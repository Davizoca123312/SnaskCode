#ifndef SNASK_ENVIRONMENT_H
#define SNASK_ENVIRONMENT_H

#include "snask_value.h"
#include <stddef.h>

// Estrutura para um par chave-valor (nome da variável e seu valor Snask)
typedef struct {
    char* name;
    SnaskValue value;
} Entry;

// Estrutura para a tabela de hash (para um escopo)
typedef struct {
    Entry** entries; // Array de ponteiros para Entry
    size_t capacity; // Capacidade da tabela de hash
    size_t count;    // Número de entradas na tabela de hash
} HashMap;

// Estrutura para um escopo (um nó na pilha de escopos)
typedef struct Environment {
    HashMap variables; // Variáveis neste escopo
    struct Environment* enclosing; // Ponteiro para o escopo pai
} Environment;

// Protótipos de funções para o ambiente
Environment* environment_create(Environment* enclosing);
void environment_free(Environment* env);

void environment_define(Environment* env, const char* name, SnaskValue value);
SnaskValue environment_get(Environment* env, const char* name);
void environment_assign(Environment* env, const char* name, SnaskValue value);

// Funções auxiliares para HashMap (internas ao environment.c)
void hashmap_init(HashMap* map);
void hashmap_free(HashMap* map);
void hashmap_put(HashMap* map, const char* key, SnaskValue value);
Entry* hashmap_get_entry(HashMap* map, const char* key);

#endif // SNASK_ENVIRONMENT_H
