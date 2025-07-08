from snask_interpreter.utils.debug import debug_print

class ControlFlowHandler:
    def __init__(self, interpreter):
        self.interpreter = interpreter
        self._resolve = interpreter._resolve
        self._execute = interpreter._execute

    def when(self, items):
        condition_node = items[0]
        body_statements = items[1:]

        debug_print(f"when: Avaliando condição: {condition_node!r}")
        condition_result = self._resolve(condition_node)
        debug_print(f"when: Resultado da condição: {condition_result!r} (tipo: {type(condition_result)})")

        debug_print(f"when: Condição avaliada: {condition_result}")
        debug_print(f"when: _conditional_block_executed antes: {self.interpreter._conditional_block_executed}")
        if condition_result:
            debug_print(f"when: Condição VERDADEIRA. Executando corpo...")
            self.interpreter._conditional_block_executed = True
            for stmt_node in body_statements:
                self._execute(stmt_node)
                if self.interpreter.returning or self.interpreter._is_break_signal or self.interpreter._is_skip_signal:
                    debug_print(f"when: Saindo do corpo do 'when' devido a returning/break/skip.")
                    break 
        else:
            debug_print(f"when: Condição FALSA. Corpo não será executado.")
            self.interpreter._conditional_block_executed = False
        debug_print(f"when: _conditional_block_executed depois: {self.interpreter._conditional_block_executed}")
        
    def whenn(self, items):
        condition_node = items[0]
        body_statements = items[1:]

        debug_print(f"whenn: Avaliando condição: {condition_node!r}")
        condition_result = self._resolve(condition_node)
        debug_print(f"whenn: Resultado da condição: {condition_result!r} (tipo: {type(condition_result)})")

        if not self.interpreter._conditional_block_executed and condition_result:
            debug_print(f"whenn: Condição VERDADEIRA e bloco anterior NÃO executado. Executando corpo...")
            self.interpreter._conditional_block_executed = True
            for stmt_node in body_statements:
                self._execute(stmt_node)
                if self.interpreter.returning or self.interpreter._is_break_signal or self.interpreter._is_skip_signal:
                    debug_print(f"whenn: Saindo do corpo do 'whenn' devido a returning/break/skip.")
                    break
        else:
            debug_print(f"whenn: Condição FALSA ou bloco anterior JÁ executado. Corpo não será executado.")

    def whenem(self, items):
        body_statements = items

        debug_print(f"whenem: Verificando se bloco anterior foi executado.")
        if not self.interpreter._conditional_block_executed:
            debug_print(f"whenem: Nenhum bloco anterior executado. Executando corpo...")
            for stmt_node in body_statements:
                self._execute(stmt_node)
                if self.interpreter.returning or self.interpreter._is_break_signal or self.interpreter._is_skip_signal:
                    debug_print(f"whenem: Saindo do corpo do 'whenem' devido a returning/break/skip.")
                    break
        else:
            debug_print(f"whenem: Bloco anterior JÁ executado. Corpo não será executado.")

    def loop_spin(self, items):
        condition_node = items[0]
        body_statements = items[1:]
        debug_print(f"loop_spin: Iniciando loop com condição {condition_node!r}")

        while self._resolve(condition_node):
            debug_print(f"loop_spin: Condição do loop VERDADEIRA.")
            for stmt_node in body_statements:
                self._execute(stmt_node)
                
                if self.interpreter._is_skip_signal:
                    debug_print(f"loop_spin: 'skipit' detectado. Indo para próxima iteração.")
                    self.interpreter._is_skip_signal = False
                    break

                if self.interpreter._is_break_signal:
                    debug_print(f"loop_spin: 'breaky' detectado. Saindo do loop.")
                    self.interpreter._is_break_signal = False
                    self.interpreter.returning = False
                    return

                if self.interpreter.returning:
                    debug_print(f"loop_spin: 'return' de função detectado. Saindo do loop e propagando.")
                    return
            
            if self.interpreter._is_skip_signal:
                self.interpreter._is_skip_signal = False
                continue

        debug_print(f"loop_spin: Condição do loop FALSA ou loop interrompido. Fim do loop_spin.")

    def loop_loopy(self, items):
        body_statements = items
        debug_print(f"loop_loopy: Iniciando loop infinito.")
        while True:
            for stmt_node in body_statements:
                self._execute(stmt_node)

                if self.interpreter._is_skip_signal:
                    debug_print(f"loop_loopy: 'skipit' detectado. Indo para próxima iteração.")
                    self.interpreter._is_skip_signal = False
                    break

                if self.interpreter._is_break_signal:
                    debug_print(f"loop_loopy: 'breaky' detectado. Saindo do loop.")
                    self.interpreter._is_break_signal = False
                    self.interpreter.returning = False
                    return

                if self.interpreter.returning:
                    debug_print(f"loop_loopy: 'return' de função detectado. Saindo do loop e propagando.")
                    return
            
            if self.interpreter._is_skip_signal:
                self.interpreter._is_skip_signal = False
                continue

    def loop_for(self, items):
        var_name = str(items[0])
        iterable_node = items[1]
        body_statements = items[2:]

        debug_print(f"loop_through: Iterando sobre {iterable_node!r} com variável {var_name}")
        iterable_collection = self._resolve(iterable_node)

        if not isinstance(iterable_collection, (list, str)):
            raise TypeError(f"loop_through: O tipo '{type(iterable_collection).__name__}' não é iterável. Esperado 'list' ou 'str'.")

        original_scope = self.interpreter.env[-1].copy()

        for item in iterable_collection:
            self.interpreter.env[-1][var_name] = item
            debug_print(f"loop_through: Variável '{var_name}' definida como '{item}'")

            for stmt_node in body_statements:
                self._execute(stmt_node)

                if self.interpreter._is_skip_signal:
                    debug_print(f"loop_through: 'skipit' detectado. Indo para próxima iteração.")
                    self.interpreter._is_skip_signal = False
                    break

                if self.interpreter._is_break_signal:
                    debug_print(f"loop_through: 'breaky' detectado. Saindo do loop.")
                    self.interpreter._is_break_signal = False
                    self.interpreter.returning = False
                    self.interpreter.env[-1] = original_scope
                    return

                if self.interpreter.returning:
                    debug_print(f"loop_through: 'return' de função detectado. Saindo do loop e propagando.")
                    self.interpreter.env[-1] = original_scope
                    return
            
            if self.interpreter._is_skip_signal:
                self.interpreter._is_skip_signal = False
                continue
        
        debug_print(f"loop_through: Fim do loop_through.")
        self.interpreter.current_scope = original_scope

    def loop_breaky(self, _):
        debug_print(f"loop_breaky: Sinal de BREAK ativado.")
        self.interpreter._is_break_signal = True

    def loop_skipit(self, _):
        debug_print(f"loop_skipit: Sinal de SKIP ativado.")
        self.interpreter._is_skip_signal = True
