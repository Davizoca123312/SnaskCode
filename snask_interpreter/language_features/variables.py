from snask_interpreter.utils.debug import debug_print
from lark import Token

class VariableHandler:
    def __init__(self, interpreter):
        self.interpreter = interpreter
        self._resolve = interpreter._resolve
        self._check_type = interpreter._check_type
        self.type = interpreter.type
        self.typeis = interpreter.typeis

    def var_decl(self, items):
        name_token = items[0]
        type_str_from_rule = self.type(items[1].children if hasattr(items[1], 'data') else items[1])
        value_node = items[2]

        name = str(name_token.value)
        value = self._resolve(value_node)

        debug_print(f"var_decl: nome='{name}', tipo_declarado='{type_str_from_rule}', valor_resolvido={value!r}")

        if name.isdigit():
         raise ValueError(f"Nome inválido para variável: '{name}' não pode ser um número.")
        
        if not self._check_type(value, type_str_from_rule):
            actual_type = self.typeis([value])
            raise TypeError(f"Tipo inválido para '{name}'. Esperado '{type_str_from_rule}', recebeu '{actual_type}' (valor: {value!r}).")

        self.interpreter.env[-1][name] = {"type": type_str_from_rule, "value": value, "constant": False}
        debug_print(f"var_decl: Variável '{name}' definida no ambiente: {self.interpreter.env[-1][name]}")

    def const_decl(self, items):
        self.var_decl(items)
        name = str(items[0].value)
        if name in self.interpreter.env[-1]:
            self.interpreter.env[-1][name]["constant"] = True
            debug_print(f"const_decl: Variável '{name}' marcada como constante.")

    def var_set(self, items):
        name_token = items[0]
        value_node = items[1]
        
        name = str(name_token.value)
        value = self._resolve(value_node)
        debug_print(f"var_set: Tentando setar '{name}' para {value!r}")

        # Search for the variable in the current and parent scopes
        found_in_scope = False
        for scope in reversed(self.interpreter.env):
            if name in scope:
                if scope[name].get("constant", False):
                    raise TypeError(f"Não é possível alterar o valor da constante '{name}'.")
                
                expected_type = scope[name]["type"]
                if not self._check_type(value, expected_type):
                    actual_type = self.typeis([value])
                    raise TypeError(f"Tipo inválido ao alterar '{name}'. Esperado '{expected_type}', recebeu '{actual_type}' (valor: {value!r}).")
                
                scope[name]["value"] = value
                debug_print(f"var_set: Variável '{name}' atualizada para: {scope[name]}")
                found_in_scope = True
                break
        
        if not found_in_scope:
            raise NameError(f"Variável '{name}' não foi declarada antes de ser definida.")

    def var_zap(self, items):
        name = str(items[0].value)
        found_in_scope = False
        for scope in reversed(self.interpreter.env):
            if name in scope:
                del scope[name]
                debug_print(f"var_zap: Variável '{name}' deletada.")
                found_in_scope = True
                break
        
        if not found_in_scope:
            print(f"AVISO: Variável '{name}' não encontrada para deletar (zap).")