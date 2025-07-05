from snask_interpreter.utils.debug import debug_print
from lark import Token, Tree

class TypeChecker:
    def __init__(self, interpreter):
        self.interpreter = interpreter

    def _check_type(self, value, expected_str_type):
     debug_print(f"_check_type: valor={value!r} (tipo {type(value).__name__}), esperado='{expected_str_type}'")
     if expected_str_type == "any": return True
     
     py_type_name = type(value).__name__

     if expected_str_type == "int": return isinstance(value, int)
     if expected_str_type == "float": return isinstance(value, (int, float)) # float pode aceitar int
     if expected_str_type == "str": return isinstance(value, str)
     if expected_str_type == "list": return isinstance(value, list)
     if expected_str_type == "dict": return isinstance(value, dict)
     if expected_str_type == "bool": return isinstance(value, bool)
     if expected_str_type == "void": return value is None
     if expected_str_type == "module": return hasattr(value, '__name__') and hasattr(value, '__file__') # Checagem simples para módulo

     # Se chegou aqui, tipo desconhecido ou incompatível
     debug_print(f"_check_type: Falhou. Valor tipo '{py_type_name}' não é '{expected_str_type}'")
     return False

    def type(self, items):
     type_val = items[0]
     if isinstance(type_val, Token):
        type_str = str(type_val.value)
     else:
        type_str = str(type_val)

     aliases = {
        "i": "int",
        "s": "str",
        "f": "float",
        "b": "bool",
        "v": "void",
        "l": "list",
        "d": "dict",
        "m": "module",
        "a": "any"
    }

     return aliases.get(type_str, type_str)

    def typeis(self, items): # items: [expr_node] ou [valor_python] se chamado internamente
        # Precisa lidar com ambos os casos. _resolve(items[0]) se for expr_node.
        # self._resolve é do interpretador, então precisamos acessá-lo via self.interpreter
        if items and isinstance(items[0], (Tree, Token)):
            val = self.interpreter._resolve(items[0])
        elif items: # Já é um valor Python
            val = items[0]
        else: # Chamada inválida
            raise ValueError("typeis chamado sem argumento.")

        py_type = type(val).__name__
        snask_types = {
            "str": "str", "int": "int", "float": "float",
            "list": "list", "dict": "dict", "bool": "bool",
            "NoneType": "void"
        }
        return snask_types.get(py_type, py_type) # Retorna nome Python se não mapeado
