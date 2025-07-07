class MathOperations:
    def __init__(self, interpreter):
        self.interpreter = interpreter
        self._resolve = interpreter._resolve
        self.typeis = interpreter.typeis

    def add(self, items):
     left = self._resolve(items[0])
     right = self._resolve(items[1])
     return left + right

    def sub(self, items):
     left = self._resolve(items[0])
     right = self._resolve(items[1])
     if isinstance(left, (int, float)) and isinstance(right, (int, float)): return left - right
     raise TypeError(f"Operação '-' não suportada entre tipos '{self.typeis([left])}' e '{self.typeis([right])}'.")

    def mul(self, items):
     left = self._resolve(items[0])
     right = self._resolve(items[1])
     if isinstance(left, (int, float)) and isinstance(right, (int, float)): return left * right
     if (isinstance(left, str) and isinstance(right, int)) or \
        (isinstance(left, int) and isinstance(right, str)): return left * right
     if (isinstance(left, list) and isinstance(right, int)) or \
        (isinstance(left, int) and isinstance(right, list)): return left * right
     raise TypeError(f"Operação '*' não suportada entre tipos '{self.typeis([left])}' e '{self.typeis([right])}'.")

    def div(self, items):
     left = self._resolve(items[0])
     right = self._resolve(items[1])
     if isinstance(left, (int, float)) and isinstance(right, (int, float)):
         if right == 0: raise ZeroDivisionError("Divisão por zero.")
         return left / right
     raise TypeError(f"Operação '/' não suportada entre tipos '{self.typeis([left])}' e '{self.typeis([right])}'.")

    def eq(self, items):
     left = self._resolve(items[0])
     right = self._resolve(items[1])
     return left == right

    def aint(self, items):
     left = self._resolve(items[0])
     right = self._resolve(items[1])
     return left != right

    def over(self, items):
     left = self._resolve(items[0]); right = self._resolve(items[1])
     if isinstance(left, (int, float, str)) and type(left) == type(right): return left > right
     if isinstance(left, (int, float)) and isinstance(right, (int, float)): return left > right
     raise TypeError(f"Operador '>' (over) não suportado entre '{self.typeis([left])}' e '{self.typeis([right])}'.")

    def under(self, items):
     left = self._resolve(items[0]); right = self._resolve(items[1])
     if isinstance(left, (int, float, str)) and type(left) == type(right): return left < right
     if isinstance(left, (int, float)) and isinstance(right, (int, float)): return left < right
     raise TypeError(f"Operador '<' (lt) não suportado entre '{self.typeis([left])}' e '{self.typeis([right])}'.")

    def overeq(self, items):
     left = self._resolve(items[0]); right = self._resolve(items[1])
     if isinstance(left, (int, float, str)) and type(left) == type(right): return left >= right
     if isinstance(left, (int, float)) and isinstance(right, (int, float)): return left >= right
     raise TypeError(f"Operador '>=' (gte) não suportado entre '{self.typeis([left])}' e '{self.typeis([right])}'.")

    def undereq(self, items):
     left = self._resolve(items[0]); right = self._resolve(items[1])
     if isinstance(left, (int, float, str)) and type(left) == type(right): return left <= right
     if isinstance(left, (int, float)) and isinstance(right, (int, float)): return left <= right
     raise TypeError(f"Operador '<=' (lte/undereq) não suportado entre '{self.typeis([left])}' e '{self.typeis([right])}'.")

    def is_(self, items):
        return self._resolve(items[0]) == self._resolve(items[1])

    def lt(self, items):
        return self.under(items)

    def gte(self, items):
        return self.overeq(items)

    def lte(self, items):
        return self.undereq(items)

    def abs(self, items):
        num = self._resolve(items[0])
        if not isinstance(num, (int, float)):
            raise TypeError("abs espera um número.")
        return abs(num)

    def smooth(self, items):
        num = self._resolve(items[0])
        if not isinstance(num, (int, float)):
            raise TypeError("smooth espera um número.")
        return round(num)