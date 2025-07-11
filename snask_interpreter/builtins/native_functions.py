class BuiltinFunctions:
    def __init__(self, interpreter):
        self.interpreter = interpreter
        self.builtins = {
            "shoo": self.shoo,
            "packdel": self.packdel,
        }

    def shoo(self, *args):
        print(*args)

    def packdel(self, list_obj, item):
        if not isinstance(list_obj, list):
            raise TypeError(f"'packdel' espera uma lista, mas recebeu {type(list_obj).__name__}")
        try:
            list_obj.remove(item)
        except ValueError:
            raise ValueError(f"Item '{item}' não encontrado na lista.")

    def register(self):
        for name, func in self.builtins.items():
            self.interpreter.functions[name] = {
                "params": {}, # Simplified for now
                "return_type": "void",
                "body_node": None,
                "native": func
            }
