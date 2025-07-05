import sys
import os
import time
from lark import Lark, UnexpectedInput

# Caminho absoluto para o diretório onde este script está
BASE_DIR = os.path.dirname(os.path.abspath(__file__))

# Importa o interpretador a partir do caminho absoluto
sys.path.insert(0, BASE_DIR)
sys.path.insert(0, os.path.join(BASE_DIR, "snask_packages"))
from snask_interpreter.core.interpreter import SnaskInterpreter

DEBUG_MODE = False  # ou False, como preferir

def carregar_bibliotecas(pasta):
    bibliotecas = {}
    libs_path = os.path.join(BASE_DIR, pasta)
    if os.path.exists(libs_path):
        for arquivo in os.listdir(libs_path):
            if arquivo.endswith(".snask"):
                nome = arquivo[:-6]
                caminho = os.path.join(libs_path, arquivo)
                with open(caminho, "r", encoding="utf-8") as f:
                    bibliotecas[nome] = f.read()
    return bibliotecas

def verificar_se_salvou(filepath):
    tempo_ultima_modificacao = os.path.getmtime(filepath)
    tempo_agora = time.time()
    if tempo_agora - tempo_ultima_modificacao < 0.5:
        print("Salve o arquivo antes de rodar.")
        sys.exit(1)

def executar_codigo(code, parser, interpreter, bibliotecas):
    try:
        tree = parser.parse(code)
        interpreter._execute_tree(tree)
    except UnexpectedInput as e:
        print("\n🚨 ERRO DE SINTAXE NO CÓDIGO 🚨")
        print(f"Linha: {e.line}, Coluna: {e.column}")
        print(f"Erro próximo de: {e.get_context(code).strip()}")
        print(f"Detalhes: {e.__class__.__name__}: {str(e).splitlines()[0]}")
        sys.exit(1)
    except Exception as e:
        print("\n🚨 ERRO INTERNO 🚨")
        print(f"Erro: {e.__class__.__name__}: {str(e)}")
        sys.exit(1)

def encontrar_primeiro_arquivo_snask():
    arquivos = [f for f in os.listdir('.') if f.endswith('.snask')]
    return arquivos[0] if arquivos else None

def main():
    input_file = sys.argv[1] if len(sys.argv) > 1 else encontrar_primeiro_arquivo_snask()
    if not input_file:
        print("Nenhum arquivo .snask encontrado.")
        sys.exit(1)

    verificar_se_salvou(input_file)

    grammar_path = os.path.join(BASE_DIR, "grammar.lark")
    with open(grammar_path, "r", encoding="utf-8") as f:
        grammar = f.read()

    parser = Lark(grammar, parser="lalr", start='start')
    interpreter = SnaskInterpreter(parser)
    bibliotecas = carregar_bibliotecas("libs")

    with open(input_file, "r", encoding="utf-8") as f:
        code = f.read()

    executar_codigo(code, parser, interpreter, bibliotecas)

if __name__ == "__main__":
    main()
