from lark import Tree, Token
from snask_interpreter.utils.debug import debug_print

class FunctionHandler:
    def __init__(self, interpreter):
        self.interpreter = interpreter
        self.env = interpreter.env
        self.functions = interpreter.functions
        self._resolve = interpreter._resolve
        self._check_type = interpreter._check_type
        self.type = interpreter.type
        self.typeis = interpreter.typeis
        self._execute = interpreter._execute
        self._execute_tree = interpreter._execute_tree

    def func_decl(self, items):
        name_token = items[0]
        idx = 1
        param_list_node = None
        if len(items) > idx and items[idx] is not None and ( (hasattr(items[idx], 'data') and items[idx].data == 'param_list') or isinstance(items[idx], list) ):
            param_list_node = items[idx]
            idx += 1
        
        return_type_node = items[idx]; idx +=1
        body_node = items[idx]

        name = str(name_token.value)
        params_dict = {}

        if param_list_node:
            for param_decl_node in param_list_node.children:
                param_name = str(param_decl_node.children[0].value)
                param_type_str = self.type(param_decl_node.children[1].children)
                params_dict[param_name] = param_type_str
        
        return_type_str = self.type(return_type_node.children)

        self.functions[name] = {"params": params_dict, "return_type": return_type_str, "body_node": body_node}
        debug_print(f"func_decl: Função '{name}' declarada. Params: {params_dict}, Retorno: {return_type_str}")

    def craft(self, items):
     debug_print(f"craft: Iniciando definição de função com items: {items}")

     func_name_token = items[0]
     func_name = str(func_name_token.value)

     return_type_idx = None
     for i in range(len(items)):
        if isinstance(items[i], Tree) and items[i].data == "type":
            return_type_idx = i
            break
        elif isinstance(items[i], str) and items[i] in ["int", "str", "float", "bool", "list", "dict", "void", "any"]:
            return_type_idx = i
            break

     if return_type_idx is None:
        raise SyntaxError("craft: Tipo de retorno não encontrado.")

     param_items = items[1:return_type_idx]
     return_type_raw = items[return_type_idx]

     body_items = [stmt for stmt in items[return_type_idx + 1:] if stmt is not None]

     params_dict = {}
     for param in param_items:
        if isinstance(param, Tree) and param.data == "param":
            pname_token, ptype_node = param.children
            pname = str(pname_token.value)
            ptype = self.type(ptype_node.children if hasattr(ptype_node, 'children') else [ptype_node])
            params_dict[pname] = ptype

     if isinstance(return_type_raw, Tree):
        return_type_str = self.type(return_type_raw.children)
     else:
        return_type_str = str(return_type_raw)

     self.functions[func_name] = {
        "params": params_dict,
        "return_type": return_type_str,
        "body_node": Tree("body", body_items)
    }

     debug_print(f"craft: Função '{func_name}' declarada com parâmetros {params_dict} e retorno '{return_type_str}'")

    def func_call(self, items):
        func_name_token = items[0]
        arg_list_node = items[1] if len(items) > 1 else None

        func_name = str(func_name_token.value)
        debug_print(f"func_call: Chamando função '{func_name}' como expressão.")

        if func_name not in self.functions:
            raise NameError(f"Função '{func_name}' não definida.")

        func_def = self.functions[func_name]
        resolved_args = []

        if arg_list_node:
             resolved_args = [self._resolve(arg_expr_node) for arg_expr_node in arg_list_node.children]
        
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

        original_env = self.env
        self.interpreter.env = self.env.copy()
        
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
            self.interpreter.env[param_name] = {"type": param_type_str, "value": arg_val, "constant": False}

        debug_print(f"_execute_function_body: Ambiente da função '{func_name}' antes da execução: {self.interpreter.env}")

        body_node = func_def["body_node"]
        if body_node and hasattr(body_node, 'children'):
            for stmt_node in body_node.children:
                self._execute(stmt_node)
                if self.interpreter.returning:
                    break 
        
        result_for_this_call = self.interpreter.return_value

        self.interpreter.env = original_env
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
