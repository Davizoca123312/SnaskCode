#ifndef SNASK_AST_H
#define SNASK_AST_H

#include "snask_value.h" // Para SnaskValue e tipos básicos

// Enumeração dos tipos de nós da AST
typedef enum {
    AST_PROGRAM,
    AST_STATEMENT_LIST,
    AST_VAR_DECLARATION,
    AST_ASSIGNMENT,
    AST_IF_STATEMENT,
    AST_WHILE_STATEMENT,
    AST_FOR_STATEMENT,
    AST_RETURN_STATEMENT,
    AST_PRINT_STATEMENT,
    AST_BLOCK,
    AST_FUNCTION_DECLARATION,
    AST_FUNCTION_CALL,
    AST_LIST_LITERAL,
    AST_IDENTIFIER,
    AST_INT_LITERAL,
    AST_FLOAT_LITERAL,
    AST_STRING_LITERAL,
    AST_BOOL_LITERAL,
    AST_NULL_LITERAL,
    AST_UNARY_EXPR,
    AST_BINARY_EXPR,
    AST_EXPRESSION_STATEMENT,
    // Adicionar mais tipos conforme a gramática for expandida
} ASTNodeType;

// Enumeração para operadores binários
typedef enum {
    OP_ADD, OP_SUB, OP_MUL, OP_DIV,
    OP_EQ, OP_NEQ, OP_LT, OP_GT, OP_LE, OP_GE,
    OP_AND, OP_OR,
} BinaryOperator;

// Enumeração para operadores unários
typedef enum {
    OP_NOT, OP_NEGATE,
} UnaryOperator;

// Forward declarations para as estruturas de nós
typedef struct ASTNode ASTNode;

// Estruturas para diferentes tipos de nós da AST

typedef struct {
    ASTNode* statements; // Lista de statements
} ASTProgram;

typedef struct {
    ASTNode** statements; // Array de ponteiros para statements
    size_t count;
    size_t capacity;
} ASTStatementList;

typedef struct {
    char* name;
    ASTNode* initializer; // Expressão de inicialização
} ASTVarDeclaration;

typedef struct {
    char* name;
    ASTNode* value; // Expressão do valor a ser atribuído
} ASTAssignment;

typedef struct {
    ASTNode* condition;
    ASTNode* then_branch;
    ASTNode* else_branch; // Pode ser NULL
} ASTIfStatement;

typedef struct {
    ASTNode* condition;
    ASTNode* body;
} ASTWhileStatement;

typedef struct {
    ASTNode* initializer; // Declaração ou expressão
    ASTNode* condition;
    ASTNode* increment;
    ASTNode* body;
} ASTForStatement;

typedef struct {
    ASTNode* value; // Expressão do valor de retorno (pode ser NULL)
} ASTReturnStatement;

typedef struct {
    ASTNode* expression;
} ASTPrintStatement;

typedef struct {
    ASTNode* statements; // Lista de statements dentro do bloco
} ASTBlock;

// Estrutura para declaração de função
typedef struct {
    char* name;
    ASTNode* params; // AST_STATEMENT_LIST de AST_IDENTIFIERs
    ASTNode* body;   // AST_BLOCK ou AST_STATEMENT_LIST
} ASTFunctionDeclaration;



// Para chamadas de função
typedef struct {
    char* name;
    ASTNode** arguments; // Array de ponteiros para expressões de argumentos
    size_t count;
    size_t capacity;
} ASTFunctionCall;

// Para literais de lista
typedef struct {
    ASTNode** elements; // Array de ponteiros para expressões de elementos
    size_t count;
    size_t capacity;
} ASTListLiteral;

typedef struct {
    char* name;
} ASTIdentifier;

typedef struct {
    long long value;
} ASTIntLiteral;

typedef struct {
    double value;
} ASTFloatLiteral;

typedef struct {
    char* value;
} ASTStringLiteral;

typedef struct {
    bool value;
} ASTBoolLiteral;

// Para expressões unárias
typedef struct {
    UnaryOperator op;
    ASTNode* operand;
} ASTUnaryExpr;

// Para expressões binárias
typedef struct {
    BinaryOperator op;
    ASTNode* left;
    ASTNode* right;
} ASTBinaryExpr;

typedef struct {
    ASTNode* expression;
} ASTExpressionStatement;

// Estrutura genérica para qualquer nó da AST
struct ASTNode {
    ASTNodeType type;
    int line; // Para depuração e mensagens de erro
    union {
        ASTProgram program;
        ASTStatementList statement_list;
        ASTVarDeclaration var_declaration;
        ASTAssignment assignment;
        ASTIfStatement if_statement;
        ASTWhileStatement while_statement;
        ASTForStatement for_statement;
        ASTReturnStatement return_statement;
        ASTPrintStatement print_statement;
        ASTBlock block;
        ASTFunctionDeclaration function_declaration;
        ASTFunctionCall function_call;
        ASTListLiteral list_literal;
        ASTIdentifier identifier;
        ASTIntLiteral int_literal;
        ASTFloatLiteral float_literal;
        ASTStringLiteral string_literal;
        ASTBoolLiteral bool_literal;
        // NULL_LITERAL não precisa de dados adicionais
        ASTUnaryExpr unary_expr;
        ASTBinaryExpr binary_expr;
        ASTExpressionStatement expression_statement;
    } data;
};

// Protótipos de funções para criação e liberação de nós da AST
ASTNode* ast_node_create(ASTNodeType type, int line);
ASTNode* ast_create_program(ASTNode* statements, int line);
ASTNode* ast_create_statement_list(int line);
void ast_statement_list_add(ASTNode* list_node, ASTNode* statement);
ASTNode* ast_create_var_declaration(char* name, ASTNode* initializer, int line);
ASTNode* ast_create_assignment(char* name, ASTNode* value, int line);
ASTNode* ast_create_if_statement(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch, int line);
ASTNode* ast_create_while_statement(ASTNode* condition, ASTNode* body, int line);
ASTNode* ast_create_for_statement(ASTNode* initializer, ASTNode* condition, ASTNode* increment, ASTNode* body, int line);
ASTNode* ast_create_return_statement(ASTNode* value, int line);
ASTNode* ast_create_print_statement(ASTNode* expression, int line);
ASTNode* ast_create_block(ASTNode* statements, int line);
ASTNode* ast_create_function_declaration(char* name, ASTNode* params, ASTNode* body, int line);
ASTNode* ast_create_function_call(char* name, int line);
void ast_function_call_add_argument(ASTNode* call_node, ASTNode* argument);
ASTNode* ast_create_list_literal(int line);
void ast_list_literal_add_element(ASTNode* list_node, ASTNode* element);
ASTNode* ast_create_identifier(char* name, int line);
ASTNode* ast_create_int_literal(long long value, int line);
ASTNode* ast_create_float_literal(double value, int line);
ASTNode* ast_create_string_literal(char* value, int line);
ASTNode* ast_create_bool_literal(bool value, int line);
ASTNode* ast_create_null_literal(int line);
ASTNode* ast_create_unary_expr(UnaryOperator op, ASTNode* operand, int line);
ASTNode* ast_create_binary_expr(BinaryOperator op, ASTNode* left, ASTNode* right, int line);
ASTNode* ast_create_expression_statement(ASTNode* expression, int line);

// Função para liberar a memória da AST
void ast_free(ASTNode* node);

// Função para imprimir a AST (para depuração)
void ast_print(ASTNode* node, int indent);

#endif // SNASK_AST_H
