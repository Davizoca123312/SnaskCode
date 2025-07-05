from snask_interpreter.utils.debug import debug_print

class TypeConversionHandler:
    def __init__(self, interpreter):
        self.interpreter = interpreter
        self.env = interpreter.env
        self._resolve = interpreter._resolve
        self.type = interpreter.type
        self.typeis = interpreter.typeis

    def convert(self, items):
        name_token = items[0]
        type_node = items[1]
        
        name = str(name_token.value)
        target_type_str = self.type(type_node.children if hasattr(type_node, 'data') else type_node)

        if name not in self.env:
            raise NameError(f"Variável '{name}' não encontrada para conversão.")

        original_value = self.env[name]["value"]
        converted_value = None
        try:
            if target_type_str == "int": converted_value = int(original_value)
            elif target_type_str == "str": converted_value = str(original_value)
            elif target_type_str == "float": converted_value = float(original_value)
            elif target_type_str == "bool": converted_value = bool(original_value)
            else:
                raise TypeError(f"Conversão para tipo '{target_type_str}' não suportada.")
        except ValueError as e:
            raise ValueError(f"Não foi possível converter '{original_value!r}' (tipo {self.typeis([original_value])}) para '{target_type_str}': {e}")

        self.env[name]["type"] = target_type_str
        self.env[name]["value"] = converted_value
        debug_print(f"convert: Variável '{name}' convertida para tipo '{target_type_str}', novo valor: {converted_value!r}")
