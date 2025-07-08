#include "snask_value.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implementação das funções de criação de SnaskValue

SnaskValue snask_value_create_null() {
    SnaskValue val;
    val.type = SNASK_NULL;
    return val;
}

SnaskValue snask_value_create_int(long long value) {
    SnaskValue val;
    val.type = SNASK_INT;
    val.data.int_val = value;
    return val;
}

SnaskValue snask_value_create_float(double value) {
    SnaskValue val;
    val.type = SNASK_FLOAT;
    val.data.float_val = value;
    return val;
}

SnaskValue snask_value_create_bool(bool value) {
    SnaskValue val;
    val.type = SNASK_BOOL;
    val.data.bool_val = value;
    return val;
}

SnaskValue snask_value_create_string(const char* value) {
    SnaskValue val;
    val.type = SNASK_STRING;
    // Aloca memória para a string e copia o conteúdo
    val.data.string_val = (char*)malloc(strlen(value) + 1);
    if (val.data.string_val == NULL) {
        fprintf(stderr, "Erro de alocação de memória para string.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(val.data.string_val, value);
    return val;
}

SnaskValue snask_value_create_list() {
    SnaskValue val;
    val.type = SNASK_LIST;
    val.data.list_val.elements = NULL;
    val.data.list_val.count = 0;
    val.data.list_val.capacity = 0;
    return val;
}

SnaskValue snask_value_create_function(ASTNode* params, ASTNode* body, Environment* closure) {
    SnaskValue val;
    val.type = SNASK_FUNCTION;
    val.data.func_val.params = params;
    val.data.func_val.body = body;
    val.data.func_val.closure = closure;
    return val;
}

// Implementação das funções de manipulação de lista
void snask_list_add(SnaskValue* list_val, SnaskValue element) {
    if (list_val->type != SNASK_LIST) {
        fprintf(stderr, "Erro: snask_list_add chamado em um não-lista.\n");
        return;
    }

    // Se a capacidade for 0, ou se estiver cheia, dobra a capacidade
    if (list_val->data.list_val.capacity == 0 || list_val->data.list_val.count == list_val->data.list_val.capacity) {
        size_t new_capacity = (list_val->data.list_val.capacity == 0) ? 4 : list_val->data.list_val.capacity * 2;
        SnaskValue* new_elements = (SnaskValue*)realloc(list_val->data.list_val.elements, new_capacity * sizeof(SnaskValue));
        if (new_elements == NULL) {
            fprintf(stderr, "Erro de realocação de memória para lista.\n");
            exit(EXIT_FAILURE);
        }
        list_val->data.list_val.elements = new_elements;
        list_val->data.list_val.capacity = new_capacity;
    }

    list_val->data.list_val.elements[list_val->data.list_val.count++] = element;
}

SnaskValue snask_list_get(SnaskValue* list_val, size_t index) {
    if (list_val->type != SNASK_LIST) {
        fprintf(stderr, "Erro: snask_list_get chamado em um não-lista.\n");
        return snask_value_create_null();
    }
    if (index >= list_val->data.list_val.count) {
        fprintf(stderr, "Erro: Índice de lista fora dos limites.\n");
        return snask_value_create_null();
    }
    return list_val->data.list_val.elements[index];
}

// Implementação da função para liberar a memória alocada por um SnaskValue
void snask_value_free(SnaskValue value) {
    switch (value.type) {
        case SNASK_STRING:
            free(value.data.string_val);
            break;
        case SNASK_LIST:
            // Libera cada elemento da lista recursivamente
            for (size_t i = 0; i < value.data.list_val.count; ++i) {
                snask_value_free(value.data.list_val.elements[i]);
            }
            free(value.data.list_val.elements);
            break;
        // Adicionar outros tipos que precisam de liberação de memória (e.g., SNASK_DICT)
        default:
            // Nada a fazer para tipos simples como INT, FLOAT, BOOL, NULL
            break;
    }
}

// Implementação da função para imprimir um SnaskValue (para depuração)
void snask_value_print(SnaskValue value) {
    switch (value.type) {
        case SNASK_NULL:
            printf("null");
            break;
        case SNASK_INT:
            printf("%lld", value.data.int_val);
            break;
        case SNASK_FLOAT:
            printf("%f", value.data.float_val);
            break;
        case SNASK_BOOL:
            printf("%s", value.data.bool_val ? "true" : "false");
            break;
        case SNASK_STRING:
            printf("\"%s\"", value.data.string_val);
            break;
        case SNASK_LIST:
            printf("[");
            for (size_t i = 0; i < value.data.list_val.count; ++i) {
                snask_value_print(value.data.list_val.elements[i]);
                if (i < value.data.list_val.count - 1) {
                    printf(", ");
                }
            }
            printf("]");
            break;
        case SNASK_FUNCTION:
            printf("<function>");
            break;
        default:
            printf("<unknown type>");
            break;
    }
}
