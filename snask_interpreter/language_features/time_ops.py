import time

class TimeOperationsHandler:
    def __init__(self, interpreter):
        self.interpreter = interpreter
        self._resolve = interpreter._resolve

    def wait_stmt(self, items):
        duration = self._resolve(items[0])
        if not isinstance(duration, (int, float)):
            raise TypeError("A duração para 'wait' deve ser um número.")
        if duration < 0:
            raise ValueError("A duração para 'wait' não pode ser negativa.")
        time.sleep(duration)
