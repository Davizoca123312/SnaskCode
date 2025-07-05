from snask_interpreter.utils.debug import debug_print
from snask_interpreter.builtins.snask_tkinter_bridge import get_snask_gui_instance

class GuiOperationsHandler:
    def __init__(self, interpreter):
        self.interpreter = interpreter
        self._resolve = interpreter._resolve
        self.snask_gui = get_snask_gui_instance(interpreter) # Pass interpreter instance

    def create_window_stmt(self, items):
        title = self._resolve(items[0])
        width = self._resolve(items[1])
        height = self._resolve(items[2])
        debug_print(f"GuiOperationsHandler: Criando janela: {title}, {width}x{height}")
        self.snask_gui.create_window(title, width, height)

    def create_button_stmt(self, items):
        text = self._resolve(items[0])
        snask_func_name = self._resolve(items[1]) # Nome da função Snask para callback
        debug_print(f"GuiOperationsHandler: Criando botão: {text}, callback: {snask_func_name}")
        self.snask_gui.create_button(text, snask_func_name)

    def create_label_stmt(self, items):
        text = self._resolve(items[0])
        debug_print(f"GuiOperationsHandler: Criando label: {text}")
        self.snask_gui.create_label(text)

    def create_entry_stmt(self, items):
        debug_print(f"GuiOperationsHandler: Criando entry.")
        self.snask_gui.create_entry()

    def start_gui_loop_stmt(self, items):
        debug_print(f"GuiOperationsHandler: Iniciando loop da GUI.")
        self.snask_gui.start_loop()
