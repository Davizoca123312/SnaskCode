from flask import Flask, request, Response
import sys
import os
from lark import Lark, UnexpectedInput

# Adiciona o diretório raiz do projeto e snask_packages ao sys.path
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, BASE_DIR)
sys.path.insert(0, os.path.join(BASE_DIR, "snask_packages"))

from snask_interpreter.core.interpreter import SnaskInterpreter

app = Flask(__name__)

# Variáveis globais para armazenar o interpretador Snask e as rotas registradas
snask_interpreter = None
snask_routes = {} # { '/path': 'snask_handler_function_name' }

def load_snask_app(app_file_path):
    global snask_interpreter
    
    grammar_path = os.path.join(BASE_DIR, "grammar.lark")
    with open(grammar_path, "r", encoding="utf-8") as f:
        grammar = f.read()

    parser = Lark(grammar, parser="lalr")
    snask_interpreter = SnaskInterpreter(parser)

    with open(app_file_path, "r", encoding="utf-8") as f:
        snask_code = f.read()

    try:
        tree = parser.parse(snask_code)
        snask_interpreter.transform(tree)
        print(f"Aplicação Snask '{app_file_path}' carregada com sucesso.")
    except UnexpectedInput as e:
        print(f"🚨 ERRO DE SINTAXE NA APLICAÇÃO SNASK 🚨")
        print(f"Linha: {e.line}, Coluna: {e.column}")
        print(f"Erro próximo de: {e.get_context(snask_code).strip()}")
        print(f"Detalhes: {e.__class__.__name__}: {str(e).splitlines()[0]}")
        sys.exit(1)
    except Exception as e:
        print(f"🚨 ERRO INTERNO AO CARREGAR APLICAÇÃO SNASK 🚨")
        print(f"Erro: {e.__class__.__name__}: {str(e)}")
        sys.exit(1)

# --- Implementação das funções da SnaskWeb que serão chamadas pelo Snask ---

# Esta função será chamada pelo Snask quando ele executar 'route(...)'
def snask_route_register(path, handler_func_name):
    print(f"[SnaskWeb Bridge] Registrando rota Snask: {path} -> {handler_func_name}")
    snask_routes[path] = handler_func_name

# Estas funções serão chamadas pelo Snask para obter informações da requisição
def snask_get_request_method():
    return request.method

def snask_get_request_path():
    return request.path

def snask_get_request_headers():
    return dict(request.headers)

def snask_get_request_body():
    return request.get_data(as_text=True)

# Esta função será chamada pelo Snask para enviar a resposta
def snask_send_response(status_code, headers, body):
    # Flask precisa de um objeto Response
    resp = Response(body, status=status_code)
    for key, value in headers.items():
        resp.headers[key] = value
    return resp

# --- Injetar as funções da ponte no interpretador Snask ---
def inject_snask_web_functions():
    if snask_interpreter:
        # Injetar a função 'route' no ambiente global do Snask
        snask_interpreter.env["route"] = {
            "type": "function",
            "value": snask_route_register, # A função Python
            "constant": True
        }
        # Injetar outras funções de requisição
        snask_interpreter.env["get_request_method"] = {"type": "function", "value": snask_get_request_method, "constant": True}
        snask_interpreter.env["get_request_path"] = {"type": "function", "value": snask_get_request_path, "constant": True}
        snask_interpreter.env["get_request_headers"] = {"type": "function", "value": snask_get_request_headers, "constant": True}
        snask_interpreter.env["get_request_body"] = {"type": "function", "value": snask_get_request_body, "constant": True}
        snask_interpreter.env["send_response"] = {"type": "function", "value": snask_send_response, "constant": True}
        print("[SnaskWeb Bridge] Funções da ponte injetadas no interpretador Snask.")

# --- Rota genérica do Flask para lidar com todas as requisições ---
@app.route('/', defaults={'path': ''}, methods=['GET', 'POST', 'PUT', 'DELETE', 'PATCH', 'HEAD', 'OPTIONS'])
@app.route('/<path:path>', methods=['GET', 'POST', 'PUT', 'DELETE', 'PATCH', 'HEAD', 'OPTIONS'])
def catch_all(path):
    full_path = '/' + path
    print(f"[Flask] Requisição recebida para: {full_path} ({request.method})")

    if full_path in snask_routes:
        handler_name = snask_routes[full_path]
        print(f"[Flask] Chamando handler Snask: {handler_name}")
        
        if handler_name not in snask_interpreter.functions:
            return f"Erro: Handler Snask '{handler_name}' não encontrado.", 500

        # Chama a função handler Snask.
        # A função Snask deve usar 'send_response' para enviar a resposta.
        # O retorno de _execute_function_body é o valor de 'back' da função Snask.
        # Se a função Snask usar 'send_response', ela já terá retornado um objeto Response.
        try:
            # A função Snask não recebe argumentos diretamente aqui,
            # ela usa get_request_method, get_request_path, etc.
            # O retorno esperado é o objeto Response do Flask.
            response_obj = snask_interpreter.func_handler._execute_function_body(
                handler_name,
                snask_interpreter.functions[handler_name],
                [] # Sem argumentos diretos para o handler Snask
            )
            if isinstance(response_obj, Response):
                return response_obj
            else:
                print(f"[Flask] Aviso: Handler Snask '{handler_name}' não retornou um objeto Response. Retornando 200 OK padrão.")
                return f"OK from Snask handler {handler_name}", 200
        except Exception as e:
            print(f"[Flask] Erro ao executar handler Snask '{handler_name}': {e}")
            return f"Erro interno do servidor Snask: {e}", 500
    else:
        return f"Rota Snask '{full_path}' não encontrada.", 404

if __name__ == '__main__':
    # Carrega a aplicação Snask (ex: app.snask)
    # Você precisará criar um arquivo app.snask na raiz do seu projeto
    # para testar isso.
    snask_app_file = os.path.join(BASE_DIR, "app.snask")
    if not os.path.exists(snask_app_file):
        print(f"ERRO: Arquivo da aplicação Snask '{snask_app_file}' não encontrado.")
        print("Por favor, crie um arquivo 'app.snask' na raiz do projeto com seu código web Snask.")
        sys.exit(1)

    load_snask_app(snask_app_file)
    inject_snask_web_functions()
    app.run(debug=True, port=8000) # Rodar na porta 8000 para evitar conflito com SnaskHub
