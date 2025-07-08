#include "environment.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16

// Função de hash simples para strings
static unsigned long hash_string(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

// Inicializa um HashMap
void hashmap_init(HashMap* map) {
    map->capacity = INITIAL_CAPACITY;
    map->count = 0;
    map->entries = (Entry**)calloc(map->capacity, sizeof(Entry*));
    if (map->entries == NULL) {
        fprintf(stderr, "Erro de alocação de memória para HashMap.\n");
        exit(EXIT_FAILURE);
    }
}

// Libera a memória de um HashMap
void hashmap_free(HashMap* map) {
    for (size_t i = 0; i < map->capacity; ++i) {
        Entry* entry = map->entries[i];
        if (entry != NULL) {
            free(entry->name);
            snask_value_free(entry->value); // Libera o valor Snask
            free(entry);
        }
    }
    free(map->entries);
    map->entries = NULL;
    map->capacity = 0;
    map->count = 0;
}

// Redimensiona o HashMap
static void hashmap_resize(HashMap* map, size_t new_capacity) {
    Entry** new_entries = (Entry**)calloc(new_capacity, sizeof(Entry*));
    if (new_entries == NULL) {
        fprintf(stderr, "Erro de realocação de memória para HashMap.\n");
        exit(EXIT_FAILURE);
    }

    // Re-insere todas as entradas existentes na nova tabela
    for (size_t i = 0; i < map->capacity; ++i) {
        Entry* entry = map->entries[i];
        if (entry != NULL) {
            unsigned long index = hash_string(entry->name) % new_capacity;
            // Lidar com colisões (sondagem linear simples)
            while (new_entries[index] != NULL) {
                index = (index + 1) % new_capacity;
            }
            new_entries[index] = entry;
        }
    }

    free(map->entries);
    map->entries = new_entries;
    map->capacity = new_capacity;
}

// Coloca um valor no HashMap
void hashmap_put(HashMap* map, const char* key, SnaskValue value) {
    // Redimensiona se a tabela estiver muito cheia
    if (map->count >= map->capacity * 0.75) { // Fator de carga
        hashmap_resize(map, map->capacity * 2);
    }

    unsigned long index = hash_string(key) % map->capacity;

    // Sondagem linear para encontrar um slot vazio ou a chave existente
    while (map->entries[index] != NULL) {
        if (strcmp(map->entries[index]->name, key) == 0) {
            // Chave existente, atualiza o valor
            snask_value_free(map->entries[index]->value); // Libera o valor antigo
            map->entries[index]->value = value;
            return;
        }
        index = (index + 1) % map->capacity;
    }

    // Slot vazio encontrado, insere nova entrada
    Entry* new_entry = (Entry*)malloc(sizeof(Entry));
    if (new_entry == NULL) {
        fprintf(stderr, "Erro de alocação de memória para Entry.\n");
        exit(EXIT_FAILURE);
    }
    new_entry->name = strdup(key);
    new_entry->value = value;
    map->entries[index] = new_entry;
    map->count++;
}

// Obtém uma entrada do HashMap
Entry* hashmap_get_entry(HashMap* map, const char* key) {
    unsigned long index = hash_string(key) % map->capacity;

    while (map->entries[index] != NULL) {
        if (strcmp(map->entries[index]->name, key) == 0) {
            return map->entries[index];
        }
        index = (index + 1) % map->capacity;
    }
    return NULL; // Chave não encontrada
}

// Cria um novo ambiente
Environment* environment_create(Environment* enclosing) {
    Environment* env = (Environment*)malloc(sizeof(Environment));
    if (env == NULL) {
        fprintf(stderr, "Erro de alocação de memória para Environment.\n");
        exit(EXIT_FAILURE);
    }
    hashmap_init(&env->variables);
    env->enclosing = enclosing;
    return env;
}

// Libera a memória de um ambiente
void environment_free(Environment* env) {
    if (env == NULL) return;
    hashmap_free(&env->variables);
    free(env);
}

// Define uma variável no ambiente atual
void environment_define(Environment* env, const char* name, SnaskValue value) {
    hashmap_put(&env->variables, name, value);
}

// Obtém o valor de uma variável, procurando nos escopos pai se necessário
SnaskValue environment_get(Environment* env, const char* name) {
    Environment* current_env = env;
    while (current_env != NULL) {
        Entry* entry = hashmap_get_entry(&current_env->variables, name);
        if (entry != NULL) {
            return entry->value; // Retorna uma cópia do valor
        }
        current_env = current_env->enclosing;
    }
    fprintf(stderr, "Erro em tempo de execução: Variável '%s' não definida.\n", name);
    exit(EXIT_FAILURE);
    return snask_value_create_null(); // Retorno de fallback
}

// Atribui um valor a uma variável existente, procurando nos escopos pai se necessário
void environment_assign(Environment* env, const char* name, SnaskValue value) {
    Environment* current_env = env;
    while (current_env != NULL) {
        Entry* entry = hashmap_get_entry(&current_env->variables, name);
        if (entry != NULL) {
            snask_value_free(entry->value); // Libera o valor antigo
            entry->value = value;
            return;
        }
        current_env = current_env->enclosing;
    }
    fprintf(stderr, "Erro em tempo de execução: Tentativa de atribuir a variável '%s' não definida.\n", name);
    exit(EXIT_FAILURE);
}
