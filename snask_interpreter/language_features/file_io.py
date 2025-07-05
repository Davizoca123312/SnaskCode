import os

class FileIOHandler:
    def __init__(self, interpreter):
        self.interpreter = interpreter
        self._resolve = interpreter._resolve
        self.env = interpreter.env

    def file_read_stmt(self, items):
        filepath_node = items[0]
        var_name_token = items[1]

        filepath = str(self._resolve(filepath_node))
        var_name = str(var_name_token.value)

        try:
            with open(filepath, "r", encoding="utf-8") as file:
                content = file.read()
            self.env[var_name] = {"type": "str", "value": content, "constant": False}
        except FileNotFoundError:
            raise FileNotFoundError(f"Arquivo '{filepath}' não encontrado para leitura.")
        except Exception as e:
            raise IOError(f"Erro ao ler arquivo '{filepath}': {e}")

    def file_write_stmt(self, items):
        filepath_node = items[0]
        content_node = items[1]

        filepath = str(self._resolve(filepath_node))
        content_to_write = str(self._resolve(content_node))

        try:
            with open(filepath, "w", encoding="utf-8") as file:
                file.write(content_to_write)
        except Exception as e:
            raise IOError(f"Erro ao escrever no arquivo '{filepath}': {e}")
