import tkinter as tk
import threading
import time

# Instância global para manter a referência ao SnaskInterpreter
_snask_interpreter_instance = None

class SnaskGUI:
    def __init__(self, interpreter=None):
        global _snask_interpreter_instance
        if interpreter:
            _snask_interpreter_instance = interpreter
        self.root = None
        self.widgets = {} # Armazena referências a widgets Tkinter se necessário para manipulação posterior
        self.callback_map = {} # Mapeia nomes de comandos Tkinter para nomes de funções Snask

    def create_window(self, title, width, height):
        if self.root:
            self.root.destroy()
        self.root = tk.Tk()
        self.root.title(title)
        self.root.geometry(f"{width}x{height}")
        print(f"Python Tkinter: Janela '{title}' criada.")
        return "window_created"

    def create_button(self, parent_id, text, snask_func_name):
        # parent_id é ignorado por simplicidade, sempre anexa à raiz
        btn = tk.Button(self.root, text=text, command=lambda: self._execute_snask_callback(snask_func_name))
        btn.pack()
        print(f"Python Tkinter: Botão '{text}' criado com callback '{snask_func_name}'.")
        return "button_created"

    def create_label(self, parent_id, text):
        lbl = tk.Label(self.root, text=text)
        lbl.pack()
        # Armazena referência do label se quisermos atualizar seu texto depois
        print(f"Python Tkinter: Label '{text}' criado.")
        return "label_created"

    def create_entry(self, parent_id):
        entry = tk.Entry(self.root)
        entry.pack()
        # Armazena referência da entrada
        print("Python Tkinter: Entry criada.")
        return "entry_created"

    def start_loop(self):
        if self.root:
            print("Python Tkinter: Iniciando loop principal em thread separada.")
            # Inicia o mainloop do Tkinter em uma thread separada
            self.gui_thread = threading.Thread(target=self.root.mainloop)
            self.gui_thread.daemon = True # Permite que a thread termine quando o programa principal termina
            self.gui_thread.start()
            print("Python Tkinter: Thread da GUI iniciada.")
            return "loop_started"
        print("Python Tkinter: Nenhuma janela para iniciar o loop.")
        return "no_window"

    def _execute_snask_callback(self, snask_func_name):
        # Isso é chamado pelo Tkinter quando um evento ocorre
        print(f"Python Tkinter: Tentando executar função Snask '{snask_func_name}'...")
        if _snask_interpreter_instance:
            # Chama o método no SnaskInterpreter para executar a função Snask
            _snask_interpreter_instance.execute_snask_function_by_name(snask_func_name)
        else:
            print("Python Tkinter: Instância do interpretador Snask não disponível para callback.")

# Instância global de SnaskGUI a ser usada pelo Snask
_snask_gui_instance = None

def get_snask_gui_instance(interpreter=None):
    global _snask_gui_instance
    if _snask_gui_instance is None:
        _snask_gui_instance = SnaskGUI(interpreter)
    return _snask_gui_instance

# Funções que o Snask pode chamar
def create_window_wrapper(title, width, height):
    return get_snask_gui_instance().create_window(title, width, height)

def create_button_wrapper(text, snask_func_name):
    return get_snask_gui_instance().create_button(None, text, snask_func_name)

def create_label_wrapper(text):
    return get_snask_gui_instance().create_label(None, text)

def create_entry_wrapper():
    return get_snask_gui_instance().create_entry(None)

def start_loop_wrapper():
    return get_snask_gui_instance().start_loop()
