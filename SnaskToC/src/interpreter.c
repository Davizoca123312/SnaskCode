#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função auxiliar para avaliar expressões
static SnaskValue evaluate_expression(ASTNode* expr, Environment* env) {
    return interpret(expr, env);
}

// Função principal para interpretar a AST
SnaskValue interpret(ASTNode* node, Environment* env) {
    if (node == NULL) {
        return snask_value_create_null();
    }

    switch (node->type) {
        case AST_PROGRAM: {
            SnaskValue result = snask_value_create_null();
            if (node->data.program.statements) {
                result = interpret(node->data.program.statements, env);
            }
            return result;
        }
        case AST_STATEMENT_LIST: {
            SnaskValue last_result = snask_value_create_null();
            for (size_t i = 0; i < node->data.statement_list.count; ++i) {
                snask_value_free(last_result); // Libera o resultado do statement anterior
                last_result = interpret(node->data.statement_list.statements[i], env);
            }
            return last_result;
        }
        case AST_VAR_DECLARATION: {
            SnaskValue value = evaluate_expression(node->data.var_declaration.initializer, env);
            environment_define(env, node->data.var_declaration.name, value);
            return snask_value_create_null(); // Declarações não retornam valor
        }
        case AST_ASSIGNMENT: {
            SnaskValue value = evaluate_expression(node->data.assignment.value, env);
            environment_assign(env, node->data.assignment.name, value);
            return value; // Atribuições retornam o valor atribuído
        }
        case AST_IF_STATEMENT: {
            SnaskValue condition_val = evaluate_expression(node->data.if_statement.condition, env);
            if (condition_val.type != SNASK_BOOL) {
                fprintf(stderr, "Erro em tempo de execução na linha %d: Condição 'if' deve ser booleana.\n", node->line);
                exit(EXIT_FAILURE);
            }
            SnaskValue result = snask_value_create_null();
            if (condition_val.data.bool_val) {
                result = interpret(node->data.if_statement.then_branch, env);
            } else if (node->data.if_statement.else_branch) {
                result = interpret(node->data.if_statement.else_branch, env);
            }
            snask_value_free(condition_val);
            return result;
        }
        case AST_WHILE_STATEMENT: {
            SnaskValue result = snask_value_create_null();
            while (true) {
                SnaskValue condition_val = evaluate_expression(node->data.while_statement.condition, env);
                if (condition_val.type != SNASK_BOOL) {
                    fprintf(stderr, "Erro em tempo de execução na linha %d: Condição 'while' deve ser booleana.\n", node->line);
                    exit(EXIT_FAILURE);
                }
                if (!condition_val.data.bool_val) {
                    snask_value_free(condition_val);
                    break;
                }
                snask_value_free(condition_val);
                snask_value_free(result); // Libera o resultado da iteração anterior
                result = interpret(node->data.while_statement.body, env);
            }
            return result;
        }
        case AST_FOR_STATEMENT: {
            // O for loop é desaçucarado para while loops
            // Inicializador
            SnaskValue init_result = snask_value_create_null();
            if (node->data.for_statement.initializer) {
                init_result = interpret(node->data.for_statement.initializer, env);
            }
            snask_value_free(init_result);

            SnaskValue loop_result = snask_value_create_null();
            while (true) {
                // Condição
                SnaskValue condition_val = evaluate_expression(node->data.for_statement.condition, env);
                if (condition_val.type != SNASK_BOOL) {
                    fprintf(stderr, "Erro em tempo de execução na linha %d: Condição 'for' deve ser booleana.\n", node->line);
                    exit(EXIT_FAILURE);
                }
                if (!condition_val.data.bool_val) {
                    snask_value_free(condition_val);
                    break;
                }
                snask_value_free(condition_val);

                // Corpo
                snask_value_free(loop_result); // Libera o resultado da iteração anterior
                loop_result = interpret(node->data.for_statement.body, env);

                // Incremento
                SnaskValue increment_result = snask_value_create_null();
                if (node->data.for_statement.increment) {
                    increment_result = interpret(node->data.for_statement.increment, env);
                }
                snask_value_free(increment_result);
            }
            return loop_result;
        }
        case AST_RETURN_STATEMENT: {
            // O tratamento de retorno será mais complexo com funções
            // Por enquanto, apenas avalia a expressão
            return evaluate_expression(node->data.return_statement.value, env);
        }
        case AST_PRINT_STATEMENT: {
            SnaskValue val = evaluate_expression(node->data.print_statement.expression, env);
            snask_value_print(val);
            printf("\n");
            snask_value_free(val);
            return snask_value_create_null();
        }
        case AST_BLOCK: {
            // Cria um novo escopo para o bloco
            Environment* block_env = environment_create(env);
            SnaskValue result = interpret(node->data.block.statements, block_env);
            environment_free(block_env);
            return result;
        }
        case AST_FUNCTION_DECLARATION: {
            SnaskValue func_val = snask_value_create_function(node->data.function_declaration.params, node->data.function_declaration.body, env);
            environment_define(env, node->data.function_declaration.name, func_val);
            return snask_value_create_null(); // Function declarations don't return a value
        }
        case AST_LIST_LITERAL: {
            SnaskValue list_val = snask_value_create_list();
            for (size_t i = 0; i < node->data.list_literal.count; ++i) {
                SnaskValue element = evaluate_expression(node->data.list_literal.elements[i], env);
                snask_list_add(&list_val, element);
            }
            return list_val;
        }
        case AST_IDENTIFIER: {
            return environment_get(env, node->data.identifier.name);
        }
        case AST_INT_LITERAL:
            return snask_value_create_int(node->data.int_literal.value);
        case AST_FLOAT_LITERAL:
            return snask_value_create_float(node->data.float_literal.value);
        case AST_STRING_LITERAL:
            return snask_value_create_string(node->data.string_literal.value);
        case AST_BOOL_LITERAL:
            return snask_value_create_bool(node->data.bool_literal.value);
        case AST_NULL_LITERAL:
            return snask_value_create_null();
        case AST_UNARY_EXPR: {
            SnaskValue operand_val = evaluate_expression(node->data.unary_expr.operand, env);
            SnaskValue result = snask_value_create_null();
            switch (node->data.unary_expr.op) {
                case OP_NOT:
                    if (operand_val.type != SNASK_BOOL) {
                        fprintf(stderr, "Erro em tempo de execução na linha %d: Operador '!' espera booleano.\n", node->line);
                        exit(EXIT_FAILURE);
                    }
                    result = snask_value_create_bool(!operand_val.data.bool_val);
                    break;
                case OP_NEGATE:
                    if (operand_val.type == SNASK_INT) {
                        result = snask_value_create_int(-operand_val.data.int_val);
                    } else if (operand_val.type == SNASK_FLOAT) {
                        result = snask_value_create_float(-operand_val.data.float_val);
                    } else {
                        fprintf(stderr, "Erro em tempo de execução na linha %d: Operador '-' unário espera número.\n", node->line);
                        exit(EXIT_FAILURE);
                    }
                    break;
            }
            snask_value_free(operand_val);
            return result;
        }
        case AST_BINARY_EXPR: {
            SnaskValue left_val = evaluate_expression(node->data.binary_expr.left, env);
            SnaskValue right_val = evaluate_expression(node->data.binary_expr.right, env);
            SnaskValue result = snask_value_create_null();

            switch (node->data.binary_expr.op) {
                case OP_ADD:
                    if (left_val.type == SNASK_INT && right_val.type == SNASK_INT) {
                        result = snask_value_create_int(left_val.data.int_val + right_val.data.int_val);
                    } else if (left_val.type == SNASK_FLOAT && right_val.type == SNASK_FLOAT) {
                        result = snask_value_create_float(left_val.data.float_val + right_val.data.float_val);
                    } else if (left_val.type == SNASK_INT && right_val.type == SNASK_FLOAT) {
                        result = snask_value_create_float((double)left_val.data.int_val + right_val.data.float_val);
                    } else if (left_val.type == SNASK_FLOAT && right_val.type == SNASK_INT) {
                        result = snask_value_create_float(left_val.data.float_val + (double)right_val.data.int_val);
                    } else if (left_val.type == SNASK_STRING && right_val.type == SNASK_STRING) {
                        char* new_str = (char*)malloc(strlen(left_val.data.string_val) + strlen(right_val.data.string_val) + 1);
                        if (new_str == NULL) { fprintf(stderr, "Erro de alocação de memória.\n"); exit(EXIT_FAILURE); }
                        strcpy(new_str, left_val.data.string_val);
                        strcat(new_str, right_val.data.string_val);
                        result = snask_value_create_string(new_str);
                        free(new_str);
                    } else {
                        fprintf(stderr, "Erro em tempo de execução na linha %d: Operador '+' espera números ou strings.\n", node->line);
                        exit(EXIT_FAILURE);
                    }
                    break;
                case OP_SUB:
                    if (left_val.type == SNASK_INT && right_val.type == SNASK_INT) {
                        result = snask_value_create_int(left_val.data.int_val - right_val.data.int_val);
                    } else if (left_val.type == SNASK_FLOAT && right_val.type == SNASK_FLOAT) {
                        result = snask_value_create_float(left_val.data.float_val - right_val.data.float_val);
                    } else if (left_val.type == SNASK_INT && right_val.type == SNASK_FLOAT) {
                        result = snask_value_create_float((double)left_val.data.int_val - right_val.data.float_val);
                    } else if (left_val.type == SNASK_FLOAT && right_val.type == SNASK_INT) {
                        result = snask_value_create_float(left_val.data.float_val - (double)right_val.data.int_val);
                    } else {
                        fprintf(stderr, "Erro em tempo de execução na linha %d: Operador '-' espera números.\n", node->line);
                        exit(EXIT_FAILURE);
                    }
                    break;
                case OP_MUL:
                    if (left_val.type == SNASK_INT && right_val.type == SNASK_INT) {
                        result = snask_value_create_int(left_val.data.int_val * right_val.data.int_val);
                    } else if (left_val.type == SNASK_FLOAT && right_val.type == SNASK_FLOAT) {
                        result = snask_value_create_float(left_val.data.float_val * right_val.data.float_val);
                    } else if (left_val.type == SNASK_INT && right_val.type == SNASK_FLOAT) {
                        result = snask_value_create_float((double)left_val.data.int_val * right_val.data.float_val);
                    } else if (left_val.type == SNASK_FLOAT && right_val.type == SNASK_INT) {
                        result = snask_value_create_float(left_val.data.float_val * (double)right_val.data.int_val);
                    }
                    else {
                        fprintf(stderr, "Erro em tempo de execução na linha %d: Operador '*' espera números.\n", node->line);
                        exit(EXIT_FAILURE);
                    }
                    break;
                case OP_DIV:
                    if (left_val.type == SNASK_INT && right_val.type == SNASK_INT) {
                        if (right_val.data.int_val == 0) { fprintf(stderr, "Erro em tempo de execução na linha %d: Divisão por zero.\n"); exit(EXIT_FAILURE); }
                        result = snask_value_create_int(left_val.data.int_val / right_val.data.int_val);
                    } else if (left_val.type == SNASK_FLOAT && right_val.type == SNASK_FLOAT) {
                        if (right_val.data.float_val == 0.0) { fprintf(stderr, "Erro em tempo de execução na linha %d: Divisão por zero.\n"); exit(EXIT_FAILURE); }
                        result = snask_value_create_float(left_val.data.float_val / right_val.data.float_val);
                    } else if (left_val.type == SNASK_INT && right_val.type == SNASK_FLOAT) {
                        if (right_val.data.float_val == 0.0) { fprintf(stderr, "Erro em tempo de execução na linha %d: Divisão por zero.\n"); exit(EXIT_FAILURE); }
                        result = snask_value_create_float((double)left_val.data.int_val / right_val.data.float_val);
                    } else if (left_val.type == SNASK_FLOAT && right_val.type == SNASK_INT) {
                        if (right_val.data.int_val == 0) { fprintf(stderr, "Erro em tempo de execução na linha %d: Divisão por zero.\n"); exit(EXIT_FAILURE); }
                        result = snask_value_create_float(left_val.data.float_val / (double)right_val.data.int_val);
                    } else {
                        fprintf(stderr, "Erro em tempo de execução na linha %d: Operador '/' espera números.\n", node->line);
                        exit(EXIT_FAILURE);
                    }
                    break;
                case OP_EQ:
                    if (left_val.type == SNASK_INT && right_val.type == SNASK_INT) {
                        result = snask_value_create_bool(left_val.data.int_val == right_val.data.int_val);
                    } else if (left_val.type == SNASK_FLOAT && right_val.type == SNASK_FLOAT) {
                        result = snask_value_create_bool(left_val.data.float_val == right_val.data.float_val);
                    } else if (left_val.type == SNASK_BOOL && right_val.type == SNASK_BOOL) {
                        result = snask_value_create_bool(left_val.data.bool_val == right_val.data.bool_val);
                    } else if (left_val.type == SNASK_STRING && right_val.type == SNASK_STRING) {
                        result = snask_value_create_bool(strcmp(left_val.data.string_val, right_val.data.string_val) == 0);
                    } else if (left_val.type == SNASK_NULL && right_val.type == SNASK_NULL) {
                        result = snask_value_create_bool(true);
                    } else {
                        result = snask_value_create_bool(false); // Tipos diferentes não são iguais
                    }
                    break;
                case OP_NEQ:
                    if (left_val.type == SNASK_INT && right_val.type == SNASK_INT) {
                        result = snask_value_create_bool(left_val.data.int_val != right_val.data.int_val);
                    } else if (left_val.type == SNASK_FLOAT && right_val.type == SNASK_FLOAT) {
                        result = snask_value_create_bool(left_val.data.float_val != right_val.data.float_val);
                    } else if (left_val.type == SNASK_BOOL && right_val.type == SNASK_BOOL) {
                        result = snask_value_create_bool(left_val.data.bool_val != right_val.data.bool_val);
                    } else if (left_val.type == SNASK_STRING && right_val.type == SNASK_STRING) {
                        result = snask_value_create_bool(strcmp(left_val.data.string_val, right_val.data.string_val) != 0);
                    } else if (left_val.type == SNASK_NULL && right_val.type == SNASK_NULL) {
                        result = snask_value_create_bool(false);
                    } else {
                        result = snask_value_create_bool(true); // Tipos diferentes são desiguais
                    }
                    break;
                case OP_LT:
                    if (left_val.type == SNASK_INT && right_val.type == SNASK_INT) {
                        result = snask_value_create_bool(left_val.data.int_val < right_val.data.int_val);
                    } else if (left_val.type == SNASK_FLOAT && right_val.type == SNASK_FLOAT) {
                        result = snask_value_create_bool(left_val.data.float_val < right_val.data.float_val);
                    } else if (left_val.type == SNASK_INT && right_val.type == SNASK_FLOAT) {
                        result = snask_value_create_bool((double)left_val.data.int_val < right_val.data.float_val);
                    } else if (left_val.type == SNASK_FLOAT && right_val.type == SNASK_INT) {
                        result = snask_value_create_bool(left_val.data.float_val < (double)right_val.data.int_val);
                    } else {
                        fprintf(stderr, "Erro em tempo de execução na linha %d: Operador '<' espera números.\n", node->line);
                        exit(EXIT_FAILURE);
                    }
                    break;
                case OP_GT:
                    if (left_val.type == SNASK_INT && right_val.type == SNASK_INT) {
                        result = snask_value_create_bool(left_val.data.int_val > right_val.data.int_val);
                    } else if (left_val.type == SNASK_FLOAT && right_val.type == SNASK_FLOAT) {
                        result = snask_value_create_bool(left_val.data.float_val > right_val.data.float_val);
                    } else if (left_val.type == SNASK_INT && right_val.type == SNASK_FLOAT) {
                        result = snask_value_create_bool((double)left_val.data.int_val > right_val.data.float_val);
                    } else if (left_val.type == SNASK_FLOAT && right_val.type == SNASK_INT) {
                        result = snask_value_create_bool(left_val.data.float_val > (double)right_val.data.int_val);
                    }
                    else {
                        fprintf(stderr, "Erro em tempo de execução na linha %d: Operador '>' espera números.\n", node->line);
                        exit(EXIT_FAILURE);
                    }
                    break;
                case OP_LE:
                    if (left_val.type == SNASK_INT && right_val.type == SNASK_INT) {
                        result = snask_value_create_bool(left_val.data.int_val <= right_val.data.int_val);
                    } else if (left_val.type == SNASK_FLOAT && right_val.type == SNASK_FLOAT) {
                        result = snask_value_create_bool(left_val.data.float_val <= right_val.data.float_val);
                    } else if (left_val.type == SNASK_INT && right_val.type == SNASK_FLOAT) {
                        result = snask_value_create_bool((double)left_val.data.int_val <= right_val.data.float_val);
                    } else if (left_val.type == SNASK_FLOAT && right_val.type == SNASK_INT) {
                        result = snask_value_create_bool(left_val.data.float_val <= (double)right_val.data.int_val);
                    } else {
                        fprintf(stderr, "Erro em tempo de execução na linha %d: Operador '<=' espera números.\n", node->line);
                        exit(EXIT_FAILURE);
                    }
                    break;
                case OP_GE:
                    if (left_val.type == SNASK_INT && right_val.type == SNASK_INT) {
                        result = snask_value_create_bool(left_val.data.int_val >= right_val.data.int_val);
                    } else if (left_val.type == SNASK_FLOAT && right_val.type == SNASK_FLOAT) {
                        result = snask_value_create_bool(left_val.data.float_val >= right_val.data.float_val);
                    } else if (left_val.type == SNASK_INT && right_val.type == SNASK_FLOAT) {
                        result = snask_value_create_bool((double)left_val.data.int_val >= right_val.data.float_val);
                    } else if (left_val.type == SNASK_FLOAT && right_val.type == SNASK_INT) {
                        result = snask_value_create_bool(left_val.data.float_val >= (double)right_val.data.int_val);
                    } else {
                        fprintf(stderr, "Erro em tempo de execução na linha %d: Operador '>=' espera números.\n", node->line);
                        exit(EXIT_FAILURE);
                    }
                    break;
                case OP_AND:
                    if (left_val.type != SNASK_BOOL || right_val.type != SNASK_BOOL) {
                        fprintf(stderr, "Erro em tempo de execução na linha %d: Operador '&&' espera booleanos.\n", node->line);
                        exit(EXIT_FAILURE);
                    }
                    result = snask_value_create_bool(left_val.data.bool_val && right_val.data.bool_val);
                    break;
                case OP_OR:
                    if (left_val.type != SNASK_BOOL || right_val.type != SNASK_BOOL) {
                        fprintf(stderr, "Erro em tempo de execução na linha %d: Operador '||' espera booleanos.\n", node->line);
                        exit(EXIT_FAILURE);
                    }
                    result = snask_value_create_bool(left_val.data.bool_val || right_val.data.bool_val);
                    break;
            }
            snask_value_free(left_val);
            snask_value_free(right_val);
            return result;
        }
        case AST_EXPRESSION_STATEMENT: {
            SnaskValue result = evaluate_expression(node->data.expression_statement.expression, env);
            snask_value_free(result); // Expressão statement não retorna valor
            return snask_value_create_null();
        }
        default:
            fprintf(stderr, "Erro em tempo de execução na linha %d: Tipo de nó AST não implementado: %d\n", node->line, node->type);
            exit(EXIT_FAILURE);
    }
}