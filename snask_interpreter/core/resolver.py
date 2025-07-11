from lark import Tree, Token
from snask_interpreter.utils.debug import debug_print
import types # Importar para verificar tipo de módulo Python

class Resolver:
    def __init__(self, interpreter):
        self.interpreter = interpreter
        # self.env = interpreter.env # Removed: Always use self.interpreter.env directly
        self.functions = interpreter.functions
        self.type_checker = interpreter.type_checker # Acesso ao TypeChecker

    def _resolve(self, val):
        debug_print(f"_resolve: Recebido: {val!r} (tipo: {type(val)})")
        debug_print(f"_resolve: Recebido: {val!r} (tipo: {type(val)})")
        if isinstance(val, Tree):
            method_name = val.data
            if method_name == "module_access_expr":
                module_name_token = val.children[0]
                member_name_token = val.children[1]

                module_name = str(module_name_token.value)
                member_name = str(member_name_token.value)

                if module_name not in self.interpreter.env:
                    raise NameError(f"Módulo '{module_name}' não encontrado.")
                
                module_info = self.interpreter.env[module_name]
                if module_info["type"] != "module":
                    raise TypeError(f"'{module_name}' não é um módulo.")
                
                module_obj = module_info["value"]

                # Tenta acessar membro de módulo Python
                if isinstance(module_obj, types.ModuleType):
                    if hasattr(module_obj, member_name):
                        return getattr(module_obj, member_name)
                    else:
                        raise AttributeError(f"Módulo Python '{module_name}' não possui membro '{member_name}'.")
                # Tenta acessar membro de módulo Snask
                elif isinstance(module_obj, dict) and "env" in module_obj and "functions" in module_obj:
                    if member_name in module_obj["env"]:
                        return module_obj["env"][member_name]["value"]
                    elif member_name in module_obj["functions"]:
                        # Retorna a definição da função para que possa ser chamada
                        return module_obj["functions"][member_name]
                    else:
                        raise NameError(f"Módulo Snask '{module_name}' não possui membro '{member_name}'.")
                else:
                    raise TypeError(f"Tipo de módulo desconhecido para '{module_name}'.")

            elif method_name == "method_call": # New handling for method_call
                obj_node = val.children[0]
                method_name_token = val.children[1]

                obj = self._resolve(obj_node)
                method_name = str(method_name_token.value)

                if not hasattr(obj, method_name):
                    raise AttributeError(f"Objeto '{obj}' não possui método ou atributo '{method_name}'.")

                member = getattr(obj, method_name)
                debug_print(f"_resolve: Resolvendo método/atributo '{method_name}' em '{obj}'. Resultado: {member!r}")
                
                if callable(member):
                    # Para chamadas de método, assumimos que não há argumentos aqui
                    # A chamada real com argumentos deve ser tratada pelo func_call
                    # ou por uma regra específica para method_call com argumentos.
                    # Por enquanto, apenas retorna o callable.
                    return member
                else:
                    return member # Return the callable method or attribute value

            elif method_name == "get_dictionary_value":
                debug_print(f"_resolve: Chamando collection_handler.get_dictionary_value para Tree: {val.data}")
                return self.interpreter.collection_handler.get_dictionary_value(val.children)

            if hasattr(self.interpreter.math_ops, method_name):
                method = getattr(self.interpreter.math_ops, method_name)
                debug_print(f"_resolve: Chamando método de MathOperations '{method_name}' para Tree: {val.data}")
                result = method(val.children)
                debug_print(f"_resolve: Método '{method_name}' retornou: {result!r}")
                return result
            else:
                method = getattr(self.interpreter, method_name, None) # Chamar método no interpretador principal
                if method:
                    debug_print(f"_resolve: Chamando método '{method_name}' para Tree: {val.data}")
                    result = method(val.children)
                    debug_print(f"_resolve: Método '{method_name}' retornou: {result!r}")
                    return result
                else:
                    raise ValueError(f"Nó da árvore com 'data' desconhecido ou não avaliável: {method_name}")

        elif isinstance(val, Token):
            debug_print(f"_resolve: Processando Token: {val.type} '{val.value}'")
            if val.type == "NUMBER":
                v_str = str(val.value)
                return float(v_str) if '.' in v_str or 'e' in v_str.lower() else int(v_str)
            elif val.type == "ESCAPED_STRING":
                # Remove as aspas externas e decodifica escapes como \n, \t, etc.
                return val.value[1:-1].encode('utf-8').decode('unicode_escape')
            elif val.type == "NAME":
                varname = val.value
                for scope in reversed(self.interpreter.env):
                    if varname in scope:
                        if isinstance(scope[varname], dict) and "value" in scope[varname]:
                            return scope[varname]['value']
                        else:
                            raise TypeError(f"Variável '{varname}' no escopo está malformada: {scope[varname]!r}")
                
                if varname == "true": return True
                elif varname == "false": return False
                elif varname in self.functions:
                    raise NameError(f"Tentativa de usar função '{varname}' como variável. Para chamar, use 'call {varname}(...)'.")
                raise NameError(f"Variável ou nome '{varname}' não encontrado.")
            else:
                debug_print(f"_resolve: Token não tratado especificamente, retornando valor: {val.value!r}")
                return val.value

        debug_print(f"_resolve: Valor já é Python, retornando: {val!r}")
        return val