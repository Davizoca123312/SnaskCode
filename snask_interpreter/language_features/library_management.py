from lark import Lark, Token
import os
from snask_interpreter.utils.debug import debug_print

class LibraryManager:
    def __init__(self, interpreter, SnaskInterpreterClass):
        self.interpreter = interpreter
        self._resolve = interpreter._resolve
        self.env = interpreter.env
        self.parser = interpreter.parser
        self._execute_tree = interpreter._execute_tree
        self.SnaskInterpreterClass = SnaskInterpreterClass # A classe do interpretador

    def use_lib(self, items):
        if isinstance(items[0], Token) and items[0].type == 'ESCAPED_STRING':
            libname_raw = items[0].value.strip('"') # Remove as aspas da string
        else:
            libname_raw = self._resolve(items[0])
        if not isinstance(libname_raw, str):
            raise TypeError("O nome da biblioteca para 'use' deve ser uma string.")

        # Tenta carregar como arquivo Snask do diretório snask_packages
        snask_lib_path_options = [
            os.path.join("snask_packages", libname_raw, "main.snask"), # Pacotes instalados via snaskpack
            os.path.join("snask_packages", libname_raw + ".snask"), # Para libs diretamente em snask_packages/
            os.path.join("libs", libname_raw + ".snask"), # Para compatibilidade com libs locais existentes
            libname_raw + ".snask" # Para libs na raiz do projeto
        ]

        actual_path_to_load = None

        # Prioriza carregar como Snask lib se o nome terminar com .snask
        if libname_raw.endswith(".snask"):
            for p in snask_lib_path_options:
                if os.path.exists(p):
                    actual_path_to_load = p
                    break
            if actual_path_to_load:
                # Se encontrado como Snask lib, processa e retorna
                if self.parser is None:
                    print("ERRO: Parser não está disponível em SnaskInterpreter para carregar biblioteca Snask.")
                    return
                try:
                    with open(actual_path_to_load, "r", encoding="utf-8") as f:
                        snask_code = f.read()
                    
                    print(f"Carregando biblioteca Snask '{libname_raw}' de '{actual_path_to_load}'...")
                    
                    module_interpreter = self.SnaskInterpreterClass(parser=self.parser)
                    module_tree = self.parser.parse(snask_code)
                    module_interpreter._execute_tree(module_tree)

                    self.env[libname_raw] = {
                        "type": "module",
                        "value": {
                            "env": module_interpreter.env,
                            "functions": module_interpreter.functions
                        },
                        "constant": True
                    }
                    print(f"Biblioteca Snask '{libname_raw}' carregada e executada em escopo isolado.")
                    return
                except Exception as e_snask:
                    print(f"ERRO ao carregar ou executar biblioteca Snask '{libname_raw}' de '{actual_path_to_load}': {e_snask}")
                    raise # Re-raise para que o erro seja capturado pelo main.py

        # Tenta carregar como módulo Python se não for um arquivo .snask
        try:
            python_module = __import__(libname_raw)
            debug_print(f"Carregando módulo Python '{libname_raw}'...")
            self.env[libname_raw] = {
                "type": "python_module",
                "value": python_module,
                "constant": True
            }
            print(f"Módulo Python '{libname_raw}' carregado com sucesso.")
            return
        except ImportError:
            debug_print(f"Módulo Python '{libname_raw}' não encontrado, tentando como Snask lib.")
            pass # Continua para tentar carregar como Snask lib

        # Fallback para carregar como Snask lib se não foi carregado ainda
        for p in snask_lib_path_options:
            if os.path.exists(p):
                actual_path_to_load = p
                break
        
        if not actual_path_to_load:
            raise FileNotFoundError(f"Biblioteca Snask '{libname_raw}' não encontrada em snask_packages/, libs/ ou na raiz do projeto.")

        if self.parser is None:
            print("ERRO: Parser não está disponível em SnaskInterpreter para carregar biblioteca Snask.")
            return

        try:
            with open(actual_path_to_load, "r", encoding="utf-8") as f:
                snask_code = f.read()
            
            print(f"Carregando biblioteca Snask '{libname_raw}' de '{actual_path_to_load}'...")
            
            module_interpreter = self.SnaskInterpreterClass(parser=self.parser)
            module_tree = self.parser.parse(snask_code)
            module_interpreter._execute_tree(module_tree)

            self.env[libname_raw] = {
                "type": "module",
                "value": {
                    "env": module_interpreter.env,
                    "functions": module_interpreter.functions
                },
                "constant": True
            }
            print(f"Biblioteca Snask '{libname_raw}' carregada e executada em escopo isolado.")

        except FileNotFoundError:
             print(f"ERRO: Arquivo da biblioteca Snask '{actual_path_to_load}' desapareceu.")
        except Exception as e_snask:
            print(f"ERRO ao carregar ou executar biblioteca Snask '{libname_raw}' de '{actual_path_to_load}': {e_snask}")
