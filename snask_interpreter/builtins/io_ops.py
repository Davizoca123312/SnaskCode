from snask_interpreter.utils.debug import debug_print
from lark.tree import Tree
import sys

class IOOperations:
    def __init__(self, interpreter):
        self.interpreter = interpreter
        self._resolve = interpreter._resolve
        self.env = interpreter.env
        self.environment = interpreter.environment
        self.type = interpreter.type

    def print_stmt(self, items):
     try:
        val_to_print_node = items[0]
        val_to_print = self._resolve(val_to_print_node)
        print(val_to_print)

     except Exception as e:
        raise RuntimeError(f"Erro ao imprimir valor: {e}")

    def input_stmt(self, items):
     name_token, type_node = items
     var_name = str(name_token.value)

     if isinstance(type_node, Tree):
        expected_type = self.type(type_node.children)
     else:
        expected_type = str(type_node)

     entrada = input()
     valor = self._converter_input(entrada, expected_type)

     self.interpreter.env[-1][var_name] = {
        "type": expected_type,
        "value": valor,
        "constant": False
     }

    def inputnum_stmt(self, items):
     name_token, type_node = items
     var_name = str(name_token.value)

     if isinstance(type_node, Tree):
        expected_type = self.type(type_node.children)
     else:
        expected_type = str(type_node)

     entrada = input()

     try:
        valor = int(entrada)
     except ValueError:
        raise TypeError(f"Valor inválido para tipo '{expected_type}': {entrada}")

     self.interpreter.env[-1][var_name] = {
        "type": expected_type,
        "value": valor,
        "constant": False
     }

    def inputtxt_stmt(self, items):
     name_token, type_node = items
     var_name = str(name_token.value)

     if isinstance(type_node, Tree):
        expected_type = self.type(type_node.children)
     else:
        expected_type = str(type_node)

     valor = input()

     if expected_type != "str":
        raise TypeError(f"grabtxt só aceita tipo 'str', mas recebeu '{expected_type}'")

     self.interpreter.env[-1][var_name] = {
        "type": expected_type,
        "value": valor,
        "constant": False
    }

    def cdr_chain(self, items):
     resolved = []
     for item in items:
        try:
            val = self._resolve(item)
            resolved.append(val)
        except Exception as e:
            debug_print(f"[CDR_CHAIN] Erro ao resolver item '{item}': {e}")
            resolved.append(f"<erro:{e}>")
     return resolved

    def _converter_input(self, entrada, expected_type):
        if expected_type == "int":
            try:
                return int(entrada)
            except ValueError:
                raise TypeError(f"Entrada inválida. Esperado um inteiro, mas recebeu '{entrada}'.")
        elif expected_type == "float":
            try:
                return float(entrada)
            except ValueError:
                raise TypeError(f"Entrada inválida. Esperado um número decimal, mas recebeu '{entrada}'.")
        elif expected_type == "bool":
            if entrada.lower() == "true": return True
            if entrada.lower() == "false": return False
            raise TypeError(f"Entrada inválida. Esperado 'true' ou 'false', mas recebeu '{entrada}'.")
        elif expected_type == "str":
            return entrada
        else:
            raise TypeError(f"Tipo de entrada '{expected_type}' não suportado para grab.")
