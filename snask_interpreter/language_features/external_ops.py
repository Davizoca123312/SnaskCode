import json
import requests
from snask_interpreter.utils.debug import debug_print

class ExternalOpsHandler:
    def __init__(self, interpreter):
        self.interpreter = interpreter
        self._resolve = interpreter._resolve

    def jsonparse(self, items):
        raw = self._resolve(items[0])
        if not isinstance(raw, str): raise TypeError("jsonparse espera uma string.")
        try:
            return json.loads(raw)
        except json.JSONDecodeError as e:
            raise ValueError(f"Erro ao decodificar JSON: {e}")

    def httpget(self, items):
        url = self._resolve(items[0])
        if not isinstance(url, str): raise TypeError("httpget espera uma URL (string).")
        try:
            response = requests.get(url, timeout=10)
            response.raise_for_status()
            return response.text
        except requests.exceptions.RequestException as e:
            raise ConnectionError(f"Erro na requisição HTTP para '{url}': {e}")
