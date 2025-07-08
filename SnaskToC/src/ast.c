#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variável global para a linha atual (usada pelo lexer/parser)
extern int yylineno;

// Função auxiliar para alocar um novo nó AST
ASTNode* ast_node_create(ASTNodeType type, int line) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    if (node == NULL) {
        fprintf(stderr, "Erro de alocação de memória para nó AST.\n");
        exit(EXIT_FAILURE);
    }
    node->type = type;
    node->line = line;
    return node;
}

// Funções de criação de nós específicos da AST

ASTNode* ast_create_program(ASTNode* statements, int line) {
    ASTNode* node = ast_node_create(AST_PROGRAM, line);
    node->data.program.statements = statements;
    return node;
}

ASTNode* ast_create_statement_list(int line) {
    ASTNode* node = ast_node_create(AST_STATEMENT_LIST, line);
    node->data.statement_list.statements = NULL;
    node->data.statement_list.count = 0;
    node->data.statement_list.capacity = 0;
    return node;
}

void ast_statement_list_add(ASTNode* list_node, ASTNode* statement) {
    if (list_node->type != AST_STATEMENT_LIST) {
        fprintf(stderr, "Erro: ast_statement_list_add chamado em um não-AST_STATEMENT_LIST.\n");
        return;
    }

    // Dobra a capacidade se necessário
    if (list_node->data.statement_list.count == list_node->data.statement_list.capacity) {
        size_t new_capacity = (list_node->data.statement_list.capacity == 0) ? 4 : list_node->data.statement_list.capacity * 2;
        ASTNode** new_statements = (ASTNode**)realloc(list_node->data.statement_list.statements, new_capacity * sizeof(ASTNode*));
        if (new_statements == NULL) {
            fprintf(stderr, "Erro de realocação de memória para lista de statements.\n");
            exit(EXIT_FAILURE);
        }
        list_node->data.statement_list.statements = new_statements;
        list_node->data.statement_list.capacity = new_capacity;
    }

    list_node->data.statement_list.statements[list_node->data.statement_list.count++] = statement;
}

ASTNode* ast_create_var_declaration(char* name, ASTNode* initializer, int line) {
    ASTNode* node = ast_node_create(AST_VAR_DECLARATION, line);
    node->data.var_declaration.name = strdup(name);
    node->data.var_declaration.initializer = initializer;
    return node;
}

ASTNode* ast_create_assignment(char* name, ASTNode* value, int line) {
    ASTNode* node = ast_node_create(AST_ASSIGNMENT, line);
    node->data.assignment.name = strdup(name);
    node->data.assignment.value = value;
    return node;
}

ASTNode* ast_create_if_statement(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch, int line) {
    ASTNode* node = ast_node_create(AST_IF_STATEMENT, line);
    node->data.if_statement.condition = condition;
    node->data.if_statement.then_branch = then_branch;
    node->data.if_statement.else_branch = else_branch;
    return node;
}

ASTNode* ast_create_while_statement(ASTNode* condition, ASTNode* body, int line) {
    ASTNode* node = ast_node_create(AST_WHILE_STATEMENT, line);
    node->data.while_statement.condition = condition;
    node->data.while_statement.body = body;
    return node;
}

ASTNode* ast_create_for_statement(ASTNode* initializer, ASTNode* condition, ASTNode* increment, ASTNode* body, int line) {
    ASTNode* node = ast_node_create(AST_FOR_STATEMENT, line);
    node->data.for_statement.initializer = initializer;
    node->data.for_statement.condition = condition;
    node->data.for_statement.increment = increment;
    node->data.for_statement.body = body;
    return node;
}

ASTNode* ast_create_return_statement(ASTNode* value, int line) {
    ASTNode* node = ast_node_create(AST_RETURN_STATEMENT, line);
    node->data.return_statement.value = value;
    return node;
}

ASTNode* ast_create_print_statement(ASTNode* expression, int line) {
    ASTNode* node = ast_node_create(AST_PRINT_STATEMENT, line);
    node->data.print_statement.expression = expression;
    return node;
}

ASTNode* ast_create_block(ASTNode* statements, int line) {
    ASTNode* node = ast_node_create(AST_BLOCK, line);
    node->data.block.statements = statements;
    return node;
}

ASTNode* ast_create_function_call(char* name, int line) {
    ASTNode* node = ast_node_create(AST_FUNCTION_CALL, line);
    node->data.function_call.name = strdup(name);
    node->data.function_call.arguments = NULL;
    node->data.function_call.count = 0;
    node->data.function_call.capacity = 0;
    return node;
}

ASTNode* ast_create_function_declaration(char* name, ASTNode* params, ASTNode* body, int line) {
    ASTNode* node = ast_node_create(AST_FUNCTION_DECLARATION, line);
    node->data.function_declaration.name = strdup(name);
    node->data.function_declaration.params = params;
    node->data.function_declaration.body = body;
    return node;
}

void ast_function_call_add_argument(ASTNode* call_node, ASTNode* argument) {
    if (call_node->type != AST_FUNCTION_CALL) {
        fprintf(stderr, "Erro: ast_function_call_add_argument chamado em um não-AST_FUNCTION_CALL.\n");
        return;
    }

    if (call_node->data.function_call.count == call_node->data.function_call.capacity) {
        size_t new_capacity = (call_node->data.function_call.capacity == 0) ? 2 : call_node->data.function_call.capacity * 2;
        ASTNode** new_arguments = (ASTNode**)realloc(call_node->data.function_call.arguments, new_capacity * sizeof(ASTNode*));
        if (new_arguments == NULL) {
            fprintf(stderr, "Erro de realocação de memória para argumentos de função.\n");
            exit(EXIT_FAILURE);
        }
        call_node->data.function_call.arguments = new_arguments;
        call_node->data.function_call.capacity = new_capacity;
    }

    call_node->data.function_call.arguments[call_node->data.function_call.count++] = argument;
}

ASTNode* ast_create_list_literal(int line) {
    ASTNode* node = ast_node_create(AST_LIST_LITERAL, line);
    node->data.list_literal.elements = NULL;
    node->data.list_literal.count = 0;
    node->data.list_literal.capacity = 0;
    return node;
}

void ast_list_literal_add_element(ASTNode* list_node, ASTNode* element) {
    if (list_node->type != AST_LIST_LITERAL) {
        fprintf(stderr, "Erro: ast_list_literal_add_element chamado em um não-AST_LIST_LITERAL.\n");
        return;
    }

    if (list_node->data.list_literal.count == list_node->data.list_literal.capacity) {
        size_t new_capacity = (list_node->data.list_literal.capacity == 0) ? 2 : list_node->data.list_literal.capacity * 2;
        ASTNode** new_elements = (ASTNode**)realloc(list_node->data.list_literal.elements, new_capacity * sizeof(ASTNode*));
        if (new_elements == NULL) {
            fprintf(stderr, "Erro de realocação de memória para elementos da lista.\n");
            exit(EXIT_FAILURE);
        }
        list_node->data.list_literal.elements = new_elements;
        list_node->data.list_literal.capacity = new_capacity;
    }

    list_node->data.list_literal.elements[list_node->data.list_literal.count++] = element;
}

ASTNode* ast_create_identifier(char* name, int line) {
    ASTNode* node = ast_node_create(AST_IDENTIFIER, line);
    node->data.identifier.name = strdup(name);
    return node;
}

ASTNode* ast_create_int_literal(long long value, int line) {
    ASTNode* node = ast_node_create(AST_INT_LITERAL, line);
    node->data.int_literal.value = value;
    return node;
}

ASTNode* ast_create_float_literal(double value, int line) {
    ASTNode* node = ast_node_create(AST_FLOAT_LITERAL, line);
    node->data.float_literal.value = value;
    return node;
}

ASTNode* ast_create_string_literal(char* value, int line) {
    ASTNode* node = ast_node_create(AST_STRING_LITERAL, line);
    node->data.string_literal.value = strdup(value);
    return node;
}

ASTNode* ast_create_bool_literal(bool value, int line) {
    ASTNode* node = ast_node_create(AST_BOOL_LITERAL, line);
    node->data.bool_literal.value = value;
    return node;
}

ASTNode* ast_create_null_literal(int line) {
    ASTNode* node = ast_node_create(AST_NULL_LITERAL, line);
    return node;
}

ASTNode* ast_create_unary_expr(UnaryOperator op, ASTNode* operand, int line) {
    ASTNode* node = ast_node_create(AST_UNARY_EXPR, line);
    node->data.unary_expr.op = op;
    node->data.unary_expr.operand = operand;
    return node;
}

ASTNode* ast_create_binary_expr(BinaryOperator op, ASTNode* left, ASTNode* right, int line) {
    ASTNode* node = ast_node_create(AST_BINARY_EXPR, line);
    node->data.binary_expr.op = op;
    node->data.binary_expr.left = left;
    node->data.binary_expr.right = right;
    return node;
}

ASTNode* ast_create_expression_statement(ASTNode* expression, int line) {
    ASTNode* node = ast_node_create(AST_EXPRESSION_STATEMENT, line);
    node->data.expression_statement.expression = expression;
    return node;
}

// Função para liberar a memória da AST recursivamente
void ast_free(ASTNode* node) {
    if (node == NULL) {
        return;
    }

    switch (node->type) {
        case AST_PROGRAM:
            ast_free(node->data.program.statements);
            break;
        case AST_STATEMENT_LIST:
            for (size_t i = 0; i < node->data.statement_list.count; ++i) {
                ast_free(node->data.statement_list.statements[i]);
            }
            free(node->data.statement_list.statements);
            break;
        case AST_VAR_DECLARATION:
            free(node->data.var_declaration.name);
            ast_free(node->data.var_declaration.initializer);
            break;
        case AST_ASSIGNMENT:
            free(node->data.assignment.name);
            ast_free(node->data.assignment.value);
            break;
        case AST_IF_STATEMENT:
            ast_free(node->data.if_statement.condition);
            ast_free(node->data.if_statement.then_branch);
            ast_free(node->data.if_statement.else_branch);
            break;
        case AST_WHILE_STATEMENT:
            ast_free(node->data.while_statement.condition);
            ast_free(node->data.while_statement.body);
            break;
        case AST_FOR_STATEMENT:
            ast_free(node->data.for_statement.initializer);
            ast_free(node->data.for_statement.condition);
            ast_free(node->data.for_statement.increment);
            ast_free(node->data.for_statement.body);
            break;
        case AST_RETURN_STATEMENT:
            ast_free(node->data.return_statement.value);
            break;
        case AST_PRINT_STATEMENT:
            ast_free(node->data.print_statement.expression);
            break;
        case AST_BLOCK:
            ast_free(node->data.block.statements);
            break;
        case AST_FUNCTION_CALL:
            free(node->data.function_call.name);
            for (size_t i = 0; i < node->data.function_call.count; ++i) {
                ast_free(node->data.function_call.arguments[i]);
            }
            free(node->data.function_call.arguments);
            break;
        case AST_LIST_LITERAL:
            for (size_t i = 0; i < node->data.list_literal.count; ++i) {
                ast_free(node->data.list_literal.elements[i]);
            }
            free(node->data.list_literal.elements);
            break;
        case AST_IDENTIFIER:
            free(node->data.identifier.name);
            break;
        case AST_STRING_LITERAL:
            free(node->data.string_literal.value);
            break;
        case AST_UNARY_EXPR:
            ast_free(node->data.unary_expr.operand);
            break;
        case AST_BINARY_EXPR:
            ast_free(node->data.binary_expr.left);
            ast_free(node->data.binary_expr.right);
            break;
        case AST_EXPRESSION_STATEMENT:
            ast_free(node->data.expression_statement.expression);
            break;
        case AST_INT_LITERAL:
        case AST_FLOAT_LITERAL:
        case AST_BOOL_LITERAL:
        case AST_NULL_LITERAL:
        case AST_FUNCTION_DECLARATION:
            free(node->data.function_declaration.name);
            ast_free(node->data.function_declaration.params);
            ast_free(node->data.function_declaration.body);
            break;
    }
    free(node);
}

// Função para imprimir a AST (para depuração)
void ast_print(ASTNode* node, int indent) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < indent; ++i) {
        printf("  ");
    }

    printf("[%d] ", node->line);

    switch (node->type) {
        case AST_PROGRAM:
            printf("PROGRAM\n");
            ast_print(node->data.program.statements, indent + 1);
            break;
        case AST_STATEMENT_LIST:
            printf("STATEMENT_LIST (%zu statements)\n", node->data.statement_list.count);
            for (size_t i = 0; i < node->data.statement_list.count; ++i) {
                ast_print(node->data.statement_list.statements[i], indent + 1);
            }
            break;
        case AST_VAR_DECLARATION:
            printf("VAR_DECL: %s =\n", node->data.var_declaration.name);
            ast_print(node->data.var_declaration.initializer, indent + 1);
            break;
        case AST_ASSIGNMENT:
            printf("ASSIGN: %s =\n", node->data.assignment.name);
            ast_print(node->data.assignment.value, indent + 1);
            break;
        case AST_IF_STATEMENT:
            printf("IF\n");
            for (int i = 0; i < indent + 1; ++i) printf("  "); printf("Condition:\n");
            ast_print(node->data.if_statement.condition, indent + 2);
            for (int i = 0; i < indent + 1; ++i) printf("  "); printf("Then:\n");
            ast_print(node->data.if_statement.then_branch, indent + 2);
            if (node->data.if_statement.else_branch) {
                for (int i = 0; i < indent + 1; ++i) printf("  "); printf("Else:\n");
                ast_print(node->data.if_statement.else_branch, indent + 2);
            }
            break;
        case AST_WHILE_STATEMENT:
            printf("WHILE\n");
            for (int i = 0; i < indent + 1; ++i) printf("  "); printf("Condition:\n");
            ast_print(node->data.while_statement.condition, indent + 2);
            for (int i = 0; i < indent + 1; ++i) printf("  "); printf("Body:\n");
            ast_print(node->data.while_statement.body, indent + 2);
            break;
        case AST_FOR_STATEMENT:
            printf("FOR\n");
            for (int i = 0; i < indent + 1; ++i) printf("  "); printf("Initializer:\n");
            ast_print(node->data.for_statement.initializer, indent + 2);
            for (int i = 0; i < indent + 1; ++i) printf("  "); printf("Condition:\n");
            ast_print(node->data.for_statement.condition, indent + 2);
            for (int i = 0; i < indent + 1; ++i) printf("  "); printf("Increment:\n");
            ast_print(node->data.for_statement.increment, indent + 2);
            for (int i = 0; i < indent + 1; ++i) printf("  "); printf("Body:\n");
            ast_print(node->data.for_statement.body, indent + 2);
            break;
        case AST_RETURN_STATEMENT:
            printf("RETURN\n");
            ast_print(node->data.return_statement.value, indent + 1);
            break;
        case AST_PRINT_STATEMENT:
            printf("PRINT\n");
            ast_print(node->data.print_statement.expression, indent + 1);
            break;
        case AST_BLOCK:
            printf("BLOCK\n");
            ast_print(node->data.block.statements, indent + 1);
            break;
        case AST_FUNCTION_CALL:
            printf("CALL: %s (args: %zu)\n", node->data.function_call.name, node->data.function_call.count);
            for (size_t i = 0; i < node->data.function_call.count; ++i) {
                ast_print(node->data.function_call.arguments[i], indent + 1);
            }
            break;
        case AST_LIST_LITERAL:
            printf("LIST_LITERAL (elements: %zu)\n", node->data.list_literal.count);
            for (size_t i = 0; i < node->data.list_literal.count; ++i) {
                ast_print(node->data.list_literal.elements[i], indent + 1);
            }
            break;
        case AST_IDENTIFIER:
            printf("IDENTIFIER: %s\n", node->data.identifier.name);
            break;
        case AST_INT_LITERAL:
            printf("INT_LITERAL: %lld\n", node->data.int_literal.value);
            break;
        case AST_FLOAT_LITERAL:
            printf("FLOAT_LITERAL: %f\n", node->data.float_literal.value);
            break;
        case AST_STRING_LITERAL:
            printf("STRING_LITERAL: \"%s\"\n", node->data.string_literal.value);
            break;
        case AST_BOOL_LITERAL:
            printf("BOOL_LITERAL: %s\n", node->data.bool_literal.value ? "true" : "false");
            break;
        case AST_NULL_LITERAL:
            printf("NULL_LITERAL\n");
            break;
        case AST_UNARY_EXPR:
            printf("UNARY_EXPR: %s\n", node->data.unary_expr.op == OP_NOT ? "NOT" : "NEGATE");
            ast_print(node->data.unary_expr.operand, indent + 1);
            break;
        case AST_BINARY_EXPR:
            printf("BINARY_EXPR: ");
            switch (node->data.binary_expr.op) {
                case OP_ADD: printf("+\n"); break;
                case OP_SUB: printf("-\n"); break;
                case OP_MUL: printf("*\n"); break;
                case OP_DIV: printf("/\n"); break;
                case OP_EQ: printf("==\n"); break;
                case OP_NEQ: printf("!= \n"); break;
                case OP_LT: printf("<\n"); break;
                case OP_GT: printf(">\n"); break;
                case OP_LE: printf("<=\n"); break;
                case OP_GE: printf(">=\n"); break;
                case OP_AND: printf("&&\n"); break;
                case OP_OR: printf("||\n"); break;
            }
            ast_print(node->data.binary_expr.left, indent + 1);
            ast_print(node->data.binary_expr.right, indent + 1);
            break;
        case AST_EXPRESSION_STATEMENT:
            printf("EXPRESSION_STATEMENT\n");
            ast_print(node->data.expression_statement.expression, indent + 1);
            break;
        case AST_FUNCTION_DECLARATION:
            printf("FUNCTION_DECLARATION: %s\n", node->data.function_declaration.name);
            for (int i = 0; i < indent + 1; ++i) printf("  "); printf("Parameters:\n");
            ast_print(node->data.function_declaration.params, indent + 2);
            for (int i = 0; i < indent + 1; ++i) printf("  "); printf("Body:\n");
            ast_print(node->data.function_declaration.body, indent + 2);
            break;
    }
}
