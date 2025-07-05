class StringOperations:
    def __init__(self, interpreter):
        self.interpreter = interpreter
        self._resolve = interpreter._resolve
        self.typeis = interpreter.typeis

    def lenof(self, items):
         val = self._resolve(items[0])
         try:
            return len(val)
         except TypeError:
            raise TypeError(f"Objeto do tipo '{self.typeis([val])}' não tem tamanho (len).")

    def toupper(self, items):
        val = self._resolve(items[0])
        if not isinstance(val, str): raise TypeError("toupper espera uma string.")
        return val.upper()

    def tolower(self, items):
        val = self._resolve(items[0])
        if not isinstance(val, str): raise TypeError("tolower espera uma string.")
        return val.lower()

    def startswith(self, items):
        val = self._resolve(items[0])
        prefix = self._resolve(items[1])
        if not isinstance(val, str) or not isinstance(prefix, str):
            raise TypeError("startswith espera dois argumentos string.")
        return val.startswith(prefix)

    def endswith(self, items):
        val = self._resolve(items[0])
        suffix = self._resolve(items[1])
        if not isinstance(val, str) or not isinstance(suffix, str):
            raise TypeError("endswith espera dois argumentos string.")
        return val.endswith(suffix)

    def split(self, items):
        s = self._resolve(items[0])
        delimiter = self._resolve(items[1])
        if not isinstance(s, str) or not isinstance(delimiter, str):
            raise TypeError("split espera dois argumentos string.")
        return s.split(delimiter)

    def join(self, items):
        lst = self._resolve(items[0])
        delimiter = self._resolve(items[1])
        if not isinstance(lst, list) or not all(isinstance(x, str) for x in lst):
            raise TypeError("join espera uma lista de strings como primeiro argumento.")
        if not isinstance(delimiter, str):
            raise TypeError("join espera uma string como segundo argumento (delimitador).")
        return delimiter.join(lst)

    def replace(self, items):
        s = self._resolve(items[0])
        old = self._resolve(items[1])
        new = self._resolve(items[2])
        if not isinstance(s, str) or not isinstance(old, str) or not isinstance(new, str):
            raise TypeError("replace espera três argumentos string.")
        return s.replace(old, new)

    def trim(self, items):
        s = self._resolve(items[0])
        if not isinstance(s, str):
            raise TypeError("trim espera uma string.")
        return s.strip()

    def finds(self, items):
        s = self._resolve(items[0])
        sub = self._resolve(items[1])
        if not isinstance(s, str) or not isinstance(sub, str):
            raise TypeError("finds espera dois argumentos string.")
        return sub in s