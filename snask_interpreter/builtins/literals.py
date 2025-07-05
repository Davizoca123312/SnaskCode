from lark import Token

class LiteralHandlers:
    def __init__(self, interpreter):
        self.interpreter = interpreter
        self.env = interpreter.env

    def number(self, token_list):
        token = token_list[0]
        val_str = str(token.value)
        return float(val_str) if '.' in val_str or 'e' in val_str.lower() else int(val_str)

    def string(self, token_list):
     raw = token_list[0].value
     return raw[1:-1].encode("utf-8").decode("unicode_escape")

    def var(self, token_list):
        varname = str(token_list[0].value)
        if varname not in self.env:
            if varname == "true": return True
            if varname == "false": return False
            raise NameError(f"Variável '{varname}' não encontrada em expressão.")
        return self.env[varname]["value"]

    def paren_expr(self, items):
        return items[0]
