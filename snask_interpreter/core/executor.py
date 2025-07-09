from lark import Tree, Token
from snask_interpreter.utils.debug import debug_print

class Executor:
    def __init__(self, interpreter):
        self.interpreter = interpreter
        self._resolve = interpreter._resolve
        self.returning = interpreter.returning
        self._is_break_signal = interpreter._is_break_signal
        self._is_skip_signal = interpreter._is_skip_signal

    def _execute(self, stmt_node):
        if self.interpreter.returning and not (self.interpreter._is_break_signal or self.interpreter._is_skip_signal):
            debug_print(f"_execute: Retornando cedo devido a 'self.returning' ser True (e não break/skip)")
            return

        if self.interpreter._is_skip_signal:
            debug_print(f"_execute: Sinal de skip detectado, não executando {stmt_node!r}")
            return

        debug_print(f"_execute: Executando nó: {stmt_node!r}")

        if stmt_node is None:
            debug_print(f"_execute: Ignorando nó None.")
            return

        if hasattr(stmt_node, "data"):
            method_name = stmt_node.data
            method = getattr(self.interpreter, method_name, None)
            
            if method:
                debug_print(f"_execute: Chamando método do Transformer '{method_name}' para: {stmt_node.data}")
                method(stmt_node.children)
            else:
                debug_print(f"_execute: Sem método Transformer para '{method_name}', tentando resolver como expressão.")
                try:
                    self._resolve(stmt_node)
                except ValueError as e:
                    print(f"AVISO: Instrução ou expressão desconhecida '{method_name}': {e}")
                except Exception as e_res:
                    print(f"ERRO ao tentar resolver instrução '{method_name}' como expressão: {e_res}")
        elif isinstance(stmt_node, Token):
            print(f"AVISO: Token '{stmt_node}' encontrado onde uma instrução era esperada. Ignorando.")
        else:
            print(f"AVISO: Objeto inesperado '{stmt_node}' (tipo {type(stmt_node)}) encontrado onde uma instrução era esperada. Ignorando.")

    def conditional_statement(self, items):
        self.interpreter._conditional_block_executed = False
        for stmt_node in items:
            if stmt_node is None:
                continue # Skip None nodes
            if not isinstance(stmt_node, Tree):
                debug_print(f"AVISO: Nó inesperado no conditional_statement: {stmt_node!r} (tipo {type(stmt_node)}). Ignorando.")
                continue

            if stmt_node.data == 'when':
                self.interpreter.control_flow_handler.when(stmt_node.children)
            elif stmt_node.data == 'whenn':
                self.interpreter.control_flow_handler.whenn(stmt_node.children)
            elif stmt_node.data == 'whenem':
                self.interpreter.control_flow_handler.whenem(stmt_node.children)
            if self.interpreter._conditional_block_executed:
                break

    def _execute_tree(self, tree):
        """ Executa todas as instruções em uma árvore de programa. """
        if not hasattr(tree, 'children'):
            return
        for stmt_node in tree.children:
            self._execute(stmt_node)
            if self.interpreter.returning or self.interpreter._is_break_signal or self.interpreter._is_skip_signal:
                debug_print(f"_execute_tree: Parando execução da árvore devido a returning/break/skip.")
                if self.interpreter._is_break_signal:
                    self.interpreter._is_break_signal = False
                if self.interpreter._is_skip_signal:
                     self.interpreter._is_skip_signal = False
                break
