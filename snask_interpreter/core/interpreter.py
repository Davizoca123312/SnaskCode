from lark import Transformer, Lark
import sys

from snask_interpreter.utils.debug import debug_print
from snask_interpreter.core.type_checker import TypeChecker
from snask_interpreter.core.resolver import Resolver
from snask_interpreter.core.executor import Executor
from snask_interpreter.language_features.variables import VariableHandler
from snask_interpreter.language_features.functions import FunctionHandler
from snask_interpreter.language_features.control_flow import ControlFlowHandler
from snask_interpreter.language_features.collections import CollectionHandler
from snask_interpreter.language_features.external_ops import ExternalOpsHandler
from snask_interpreter.language_features.file_io import FileIOHandler
from snask_interpreter.language_features.time_ops import TimeOperationsHandler
from snask_interpreter.language_features.type_conversion import TypeConversionHandler
from snask_interpreter.language_features.library_management import LibraryManager
from snask_interpreter.language_features.gui_ops import GuiOperationsHandler
from snask_interpreter.builtins.string_ops import StringOperations
from snask_interpreter.builtins.io_ops import IOOperations
from snask_interpreter.builtins.math_ops import MathOperations
from snask_interpreter.builtins.literals import LiteralHandlers
from snask_interpreter.builtins.snask_tkinter_bridge import get_snask_gui_instance

class SnaskInterpreter(Transformer):
    def __init__(self, parser=None):
        self.env = [{}] # Stack of scopes, global scope at index 0
        self.functions = {}
        self.returning = False
        self.return_value = None
        self.parser = parser
        self.environment = {}
        self._is_break_signal = False
        self._is_skip_signal = False
        self._conditional_block_executed = False
        self.reactive_rules = []
        self.triggered_conditions = set()

        # Inicializa os módulos
        
        self.type_checker = TypeChecker(self)
        self.resolver = Resolver(self)
        self.executor = Executor(self)
        self.var_handler = VariableHandler(self)
        self.func_handler = FunctionHandler(self)
        self.control_flow_handler = ControlFlowHandler(self)
        self.collection_handler = CollectionHandler(self)
        self.external_ops_handler = ExternalOpsHandler(self)
        self.file_io_handler = FileIOHandler(self)
        self.time_ops_handler = TimeOperationsHandler(self)
        self.type_conversion_handler = TypeConversionHandler(self)
        self.library_manager = LibraryManager(self, SnaskInterpreter)
        self.string_ops = StringOperations(self)
        self.io_ops = IOOperations(self)
        self.math_ops = MathOperations(self)
        self.literal_handlers = LiteralHandlers(self)
        self.gui_ops_handler = GuiOperationsHandler(self)

    def push_scope(self, new_scope=None):
        if new_scope is None:
            new_scope = {}
        self.env.append(new_scope)
        debug_print(f"Scope pushed. Current stack depth: {len(self.env)}")

    def pop_scope(self):
        if len(self.env) > 1: # Don't pop the global scope
            self.env.pop()
            debug_print(f"Scope popped. Current stack depth: {len(self.env)}")
        else:
            debug_print("Cannot pop global scope.")

    def execute_snask_function_by_name(self, func_name):
        # Este método será chamado pelo Python para executar uma função Snask
        debug_print(f"SnaskInterpreter: Recebida chamada de callback para a função Snask: {func_name}")
        if func_name in self.functions:
            func_def = self.functions[func_name]
            # Para callbacks, assumimos que não há argumentos passados do Tkinter para a função Snask
            self.func_handler._execute_function_body(func_name, func_def, [])
        else:
            print(f"ERRO: Função Snask '{func_name}' não encontrada para callback.")

    # Métodos que delegam para as classes auxiliares
    def _resolve(self, val): return self.resolver._resolve(val)
    def _execute(self, stmt_node): return self.executor._execute(stmt_node)
    def _execute_tree(self, tree): return self.executor._execute_tree(tree)
    def _check_type(self, value, expected_str_type): return self.type_checker._check_type(value, expected_str_type)
    def type(self, items): return self.type_checker.type(items)
    def typeis(self, items): return self.type_checker.typeis(items)

    

    # Delegação para VariableHandler
    def var_decl(self, items): return self.var_handler.var_decl(items)
    def const_decl(self, items): return self.var_handler.const_decl(items)
    def var_set(self, items): return self.var_handler.var_set(items)
    def var_zap(self, items): return self.var_handler.var_zap(items)

    # Delegação para FunctionHandler
    def func_decl(self, items): return self.func_handler.func_decl(items)
    def craft(self, items): return self.func_handler.craft(items)
    def func_call(self, items): return self.func_handler.func_call(items)
    def func_call_stmt(self, items): return self.func_handler.func_call_stmt(items)
    def _execute_function_body(self, func_name, func_def, resolved_args): return self.func_handler._execute_function_body(func_name, func_def, resolved_args)
    def return_stmt(self, items): return self.func_handler.return_stmt(items)

    # Delegação para ControlFlowHandler
    def when(self, items): return self.control_flow_handler.when(items)
    def whenn(self, items): return self.control_flow_handler.whenn(items)
    def whenem(self, items): return self.control_flow_handler.whenem(items)
    def loop_spin(self, items): return self.control_flow_handler.loop_spin(items)
    def loop_loopy(self, items): return self.control_flow_handler.loop_loopy(items)
    def loop_for(self, items): return self.control_flow_handler.loop_for(items)
    def loop_breaky(self, _): return self.control_flow_handler.loop_breaky(_)
    def loop_skipit(self, _): return self.control_flow_handler.loop_skipit(_)
    def conditional_statement(self, items): return self.executor.conditional_statement(items)

    # Delegação para GuiOperationsHandler
    def create_window(self, items): return self.gui_ops_handler.create_window_stmt(items)
    def create_button(self, items): return self.gui_ops_handler.create_button_stmt(items)
    def create_label(self, items): return self.gui_ops_handler.create_label_stmt(items)
    def create_entry(self, items): return self.gui_ops_handler.create_entry_stmt(items)
    def start_gui_loop(self, items): return self.gui_ops_handler.start_gui_loop_stmt(items)

    # Delegação para CollectionHandler
    def list_literal(self, items): return self.collection_handler.list_literal(items)
    def pack_decl(self, items): return self.collection_handler.pack_decl(items)
    def pack_get(self, items): return self.collection_handler.pack_get(items)
    def pack_add(self, items): return self.collection_handler.pack_add(items)
    def dict_literal(self, items): return self.collection_handler.dict_literal(items)
    def box_decl(self, items): return self.collection_handler.box_decl(items)
    def box_put(self, items): return self.collection_handler.box_put(items)
    def index_access(self, items): return self.collection_handler.index_access(items)
    def toss(self, items): return self.collection_handler.toss(items)
    def pluck(self, items): return self.collection_handler.pluck(items)
    def tuck(self, items): return self.collection_handler.tuck(items)
    def order(self, items): return self.collection_handler.order(items)
    def locks(self, items): return self.collection_handler.locks(items)
    def treasures(self, items): return self.collection_handler.treasures(items)

    # Delegação para ExternalOpsHandler
    def jsonparse(self, items): return self.external_ops_handler.jsonparse(items)
    def httpget(self, items): return self.external_ops_handler.httpget(items)

    # Delegação para FileIOHandler
    def file_read_stmt(self, items): return self.file_io_handler.file_read_stmt(items)
    def file_write_stmt(self, items): return self.file_io_handler.file_write_stmt(items)

    # Delegação para TimeOperationsHandler
    def wait_stmt(self, items): return self.time_ops_handler.wait_stmt(items)

    # Delegação para TypeConversionHandler
    def convert(self, items): return self.type_conversion_handler.convert(items)

    # Delegação para LibraryManager
    def use_lib(self, items): return self.library_manager.use_lib(items)

    # Delegação para StringOperations
    def lenof(self, items): return self.string_ops.lenof(items)
    def toupper(self, items): return self.string_ops.toupper(items)
    def tolower(self, items): return self.string_ops.tolower(items)
    def startswith(self, items): return self.string_ops.startswith(items)
    def endswith(self, items): return self.string_ops.endswith(items)

    # Delegação para IOOperations
    def print_stmt(self, items): return self.io_ops.print_stmt(items)
    def input_stmt(self, items): return self.io_ops.input_stmt(items)
    def inputnum_stmt(self, items): return self.io_ops.inputnum_stmt(items)
    def inputtxt_stmt(self, items): return self.io_ops.inputtxt_stmt(items)
    def cdr_chain(self, items): return self.io_ops.cdr_chain(items)

    # Delegação para MathOperations
    def add(self, items): return self.math_ops.add(items)
    def sub(self, items): return self.math_ops.sub(items)
    def mul(self, items): return self.math_ops.mul(items)
    def div(self, items): return self.math_ops.div(items)
    def eq(self, items): return self.math_ops.eq(items)
    def aint(self, items): return self.math_ops.aint(items)
    def over(self, items): return self.math_ops.over(items)
    def under(self, items): return self.math_ops.under(items)
    def overeq(self, items): return self.math_ops.overeq(items)
    def undereq(self, items): return self.math_ops.undereq(items)
    def is_(self, items): return self.math_ops.is_(items)
    def lt(self, items): return self.math_ops.lt(items)
    def gte(self, items): return self.math_ops.gte(items)
    def abs(self, items): return self.math_ops.abs(items)
    def round(self, items): return self.math_ops.round(items)

    # Delegação para LiteralHandlers
    def number(self, token_list): return self.literal_handlers.number(token_list)
    def string(self, token_list): return self.literal_handlers.string(token_list)
    def var(self, token_list): return self.literal_handlers.var(token_list)
    def paren_expr(self, items): return self.literal_handlers.paren_expr(items)

    def _check_reactive_rules(self):
        for i, (condition_node, body_nodes) in enumerate(self.reactive_rules):
            try:
                resolved = self._resolve(condition_node)
                condition_key = f"reactive_rule_{i}"

                if resolved:
                    if condition_key not in self.triggered_conditions:
                        for stmt_node in body_nodes:
                            self._execute(stmt_node)
                            if self.returning or self._is_break_signal or self._is_skip_signal: return
                        self.triggered_conditions.add(condition_key)
                else:
                    if condition_key in self.triggered_conditions:
                        self.triggered_conditions.remove(condition_key)
            except Exception as e:
                print(f"Erro na regra reativa {i} (condição: {condition_node}): {e}")
