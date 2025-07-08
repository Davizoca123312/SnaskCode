#ifndef SNASK_VALUE_H
#define SNASK_VALUE_H

#include <stdbool.h> // Para bool
#include <stddef.h>  // Para size_t

// Enumeração dos tipos de valor que Snask pode ter
typedef enum {
    SNASK_NULL,
    SNASK_INT,
    SNASK_FLOAT,
    SNASK_BOOL,
    SNASK_STRING,
    SNASK_LIST,
    SNASK_FUNCTION, // Para funções definidas pelo usuário ou built-in
    // Adicionar outros tipos conforme necessário (e.g., SNASK_DICT, SNASK_OBJECT)
} SnaskValueType;

typedef struct {
    struct SnaskValue* elements; // Ponteiro para os elementos da lista
    size_t count;                // Número atual de elementos
    size_t capacity;             // Capacidade alocada
} SnaskList;

// Estrutura para representar uma função (definida pelo usuário)
typedef struct {
    struct ASTNode* params; // ASTNode do tipo AST_STATEMENT_LIST contendo AST_IDENTIFIERs para os parâmetros
    struct ASTNode* body;   // ASTNode do tipo AST_BLOCK ou AST_STATEMENT para o corpo da função
    struct Environment* closure; // Ambiente onde a função foi definida (para fechamentos)
} SnaskFunction;

// União para armazenar o valor real, dependendo do tipo
typedef union {
    long long int_val;
    double float_val;
    bool bool_val;
    char* string_val;
    SnaskList list_val;
    SnaskFunction func_val;
} SnaskValueData;

// Estrutura principal para qualquer valor Snask
typedef struct SnaskValue {
    SnaskValueType type;
    SnaskValueData data;
} SnaskValue;

// Protótipos de funções para criação e manipulação de SnaskValue
SnaskValue snask_value_create_null();
SnaskValue snask_value_create_int(long long value);
SnaskValue snask_value_create_float(double value);
SnaskValue snask_value_create_bool(bool value);
SnaskValue snask_value_create_string(const char* value);
SnaskValue snask_value_create_list(); // Cria uma lista vazia
SnaskValue snask_value_create_function(struct ASTNode* params, struct ASTNode* body, struct Environment* closure);

// Funções de manipulação de lista
void snask_list_add(SnaskValue* list_val, SnaskValue element);
SnaskValue snask_list_get(SnaskValue* list_val, size_t index);

// Função para liberar a memória alocada por um SnaskValue (especialmente strings e listas)
void snask_value_free(SnaskValue value);

// Função para imprimir um SnaskValue (para depuração)
void snask_value_print(SnaskValue value);

#endif // SNASK_VALUE_H
