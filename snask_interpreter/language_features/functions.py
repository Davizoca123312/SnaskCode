from lark import Tree, Token
from snask_interpreter.utils.debug import debug_print

class FunctionHandler:
    def __init__(self, interpreter):
        self.interpreter = interpreter
        # self.env = interpreter.env # Removed: Always use self.interpreter.env directly
        self.functions = interpreter.functions
        self._resolve = interpreter._resolve
        self._check_type = interpreter._check_type
        self.type = interpreter.type
        self.typeis = interpreter.typeis
        self._execute = interpreter._execute
        self._execute_tree = interpreter._execute_tree

    

    def function(self, items):
     debug_print(f"function: Iniciando definição de função com items: {items}")

     # Nova ordem: type, name, params, body
     return_type_node = items[0]
     func_name_token = items[1]
     param_list_node = items[2]
     body_node = items[3]

     func_name = str(func_name_token.value)

     return_type_str = self.type(return_type_node.children)

     params_dict = {}
     if param_list_node:
         for param_decl_node in param_list_node.children:
             # A ordem em param agora é [type, name]
             param_type_node = param_decl_node.children[0]
             param_name_token = param_decl_node.children[1]
           
             param_name = str(param_name_token.value)
             param_type_str = self.type(param_type_node.children)
             params_dict[param_name] = param_type_str

     self.functions[func_name] = {
         "params": params_dict,
         "return_type": return_type_str,
         "body_node": body_node
     }

     debug_print(f"function: Função '{func_name}' declarada com parâmetros {params_dict} e retorno '{return_type_str}'")

    def func_call(self, items):
        func_name_token = items[0]
        arg_expr_nodes = items[1:]

        if isinstance(func_name_token, Tree) and func_name_token.data == 'module_access_expr':
            module_name = str(func_name_token.children[0].value)
            member_name = str(func_name_token.children[1].value)
            
            if module_name not in self.interpreter.env:
                raise NameError(f"Módulo '{module_name}' não encontrado.")

            module_info = self.interpreter.env[module_name]
            resolved_args = [self._resolve(arg_expr_node) for arg_expr_node in arg_expr_nodes]

            if module_info["type"] == "python_module":
                python_module = module_info["value"]
                if not hasattr(python_module, member_name):
                    raise AttributeError(f"Módulo Python '{module_name}' não possui membro '{member_name}'.")
                
                member = getattr(python_module, member_name)
                if callable(member):
                    debug_print(f"Chamando método Python '{module_name}.{member_name}' com args: {resolved_args}")
                    return member(*resolved_args)
                else:
                    debug_print(f"Acessando atributo Python '{module_name}.{member_name}'")
                    return member
            elif module_info["type"] == "module": # Módulo Snask
                module_env = module_info["value"]["env"]
                module_functions = module_info["value"]["functions"]

                if member_name not in module_functions:
                    raise NameError(f"Função '{member_name}' não definida no módulo Snask '{module_name}'.")
                
                func_def = module_functions[member_name]
                original_env = self.interpreter.env
                self.interpreter.env = module_env
                result = self._execute_function_body(member_name, func_def, resolved_args)
                self.interpreter.env = original_env
                return result
            else:
                raise TypeError(f"Tipo de módulo desconhecido para '{module_name}': {module_info['type']}")
        else:
            func_name = str(func_name_token.value)
            debug_print(f"func_call: Chamando função '{func_name}' como expressão.")

            if func_name not in self.functions:
                raise NameError(f"Função '{func_name}' não definida.")

            func_def = self.functions[func_name]
            resolved_args = []

            resolved_args = [self._resolve(arg_expr_node) for arg_expr_node in arg_expr_nodes]
            
            return self._execute_function_body(func_name, func_def, resolved_args)

    def func_call_stmt(self, items):
        debug_print(f"func_call_stmt: Executando chamada de função como instrução.")
        self._resolve(items[0])

    def _execute_function_body(self, func_name, func_def, resolved_args):
        expected_params_def = func_def["params"]

        if len(resolved_args) != len(expected_params_def):
            raise TypeError(
                f"Função '{func_name}' espera {len(expected_params_def)} argumentos ({list(expected_params_def.keys())}), "
                f"mas recebeu {len(resolved_args)}."
            )

        self.interpreter.push_scope()
        
        original_returning = self.interpreter.returning
        original_return_value = self.interpreter.return_value
        self.interpreter.returning = False
        self.interpreter.return_value = None
        self.interpreter._is_break_signal = False
        self.interpreter._is_skip_signal = False

        for (param_name, param_type_str), arg_val in zip(expected_params_def.items(), resolved_args):
            if not self._check_type(arg_val, param_type_str):
                actual_arg_type = self.typeis([arg_val])
                raise TypeError(
                    f"Argumento '{param_name}' para função '{func_name}': esperado '{param_type_str}', "
                    f"recebeu '{actual_arg_type}' (valor: {arg_val!r})."
                )
            self.interpreter.env[-1][param_name] = {"type": param_type_str, "value": arg_val, "constant": False}

        debug_print(f"_execute_function_body: Ambiente da função '{func_name}' antes da execução: {self.interpreter.env}")

        body_node = func_def["body_node"]
        if body_node and hasattr(body_node, 'children'):
            for stmt_node in body_node.children:
                self._execute(stmt_node)
                if self.interpreter.returning:
                    break 
        
        result_for_this_call = self.interpreter.return_value

        self.interpreter.pop_scope()
        self.interpreter.returning = original_returning
        self.interpreter.return_value = original_return_value

        expected_return_type = func_def["return_type"]
        if not self._check_type(result_for_this_call, expected_return_type):
            actual_returned_type = self.typeis([result_for_this_call])
            raise TypeError(
                f"Função '{func_name}' deveria retornar '{expected_return_type}', "
                f"mas retornou '{actual_returned_type}' (valor: {result_for_this_call!r})."
            )
        
        debug_print(f"_execute_function_body: Função '{func_name}' retornando: {result_for_this_call!r}")
        return result_for_this_call

    def return_stmt(self, items):
        if items and items[0] is not None:
            self.interpreter.return_value = self._resolve(items[0])
        else:
            self.interpreter.return_value = None
        self.interpreter.returning = True
        debug_print(f"return_stmt: 'returning' setado para True, valor: {self.interpreter.return_value!r}")
