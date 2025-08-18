#include "../../headers/functions/ht.h"
#include "../../headers/ressources.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

/* ---------- utils ---------- */
static void free_rules_table(char ***tab, int nb) {
    if (!tab) return;
    for (int i = 0; i < nb; i++) {
        if (tab[i]) {
            free(tab[i][0]);
            free(tab[i][1]);
            free(tab[i]);
        }
    }
    free(tab);
}

static size_t round_up_pow2(size_t n) {
    size_t p = 8;
    while (p < n) p <<= 1;
    return p;
}

/* ---------- create/destroy ---------- */
ht* ht_create(int initial_capacity) {
    ht *table = malloc(sizeof(ht));
    if (!table) return NULL;

    table->length = 0;
    table->capacity = (int)round_up_pow2((size_t)initial_capacity);

    table->entries = calloc(table->capacity, sizeof(ht_entry));
    if (!table->entries) {
        free(table);
        return NULL;
    }
    return table;
}

void ht_destroy(ht* table) {
    if (!table) return;
    for (size_t i = 0; i < table->capacity; i++) {
        if (table->entries[i].key != NULL) {
            free((void*)table->entries[i].key);
            free_rules_table(table->entries[i].tableau_etats,
                             table->entries[i].nb_rules_by_etat);
        }
    }
    free(table->entries);
    free(table);
}

/* ---------- hash (FNV-1a 64) ---------- */
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME  1099511628211UL

static uint64_t hash_key(const char* key) {
    uint64_t hash = FNV_OFFSET;
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

/* ---------- get/set ---------- */
ht_entry* ht_get(ht* table, const char* key) {
    uint64_t hash = hash_key(key);
    size_t index = (size_t)(hash & (uint64_t)(table->capacity - 1));

    while (table->entries[index].key != NULL) {
        if (strcmp(key, table->entries[index].key) == 0) {
            return &table->entries[index];
        }
        index++;
        if (index >= table->capacity) index = 0;
    }
    return NULL;
}

const char* ht_set_entry(ht_entry* entries, size_t capacity,
        const char* key, char ***tableau_etats, size_t* plength, int nb_rules_by_etat) {
    uint64_t hash = hash_key(key);
    size_t index = (size_t)(hash & (uint64_t)(capacity - 1));

    while (entries[index].key != NULL) {
        if (strcmp(key, entries[index].key) == 0) {
            // Remplace la valeur (penser à libérer l’ancienne avant d’appeler si besoin)
            entries[index].tableau_etats = tableau_etats;
            entries[index].nb_rules_by_etat = nb_rules_by_etat;
            return entries[index].key;
        }
        if (++index >= capacity) index = 0;
    }

    if (plength != NULL) {
        char *dup = strdup(key);
        if (!dup) return NULL;
        key = dup;
        (*plength)++;
    }

    entries[index].key = (char*)key;
    entries[index].tableau_etats = tableau_etats;
    entries[index].nb_rules_by_etat = nb_rules_by_etat;
    return key;
}

static bool ht_expand(ht* table) {
    size_t new_capacity = table->capacity * 2;
    if (new_capacity < table->capacity) return false;

    ht_entry* new_entries = calloc(new_capacity, sizeof(ht_entry));
    if (!new_entries) return false;

    for (size_t i = 0; i < table->capacity; i++) {
        ht_entry entry = table->entries[i];
        if (entry.key != NULL) {
            // On réinsère en conservant nb_rules_by_etat propre à l’entrée
            ht_set_entry(new_entries, new_capacity, entry.key,
                         entry.tableau_etats, NULL, entry.nb_rules_by_etat);
        }
    }

    free(table->entries);
    table->entries = new_entries;
    table->capacity = (int)new_capacity;
    return true;
}

const char* ht_set(ht* table, const char* key, char ***tableau_etats, int nb_rules_by_etat) {
    assert(tableau_etats != NULL);
    if (!tableau_etats) return NULL;

    // facteur de charge 0.5 (simple et efficace avec addressing linéaire)
    if (table->length >= table->capacity / 2) {
        if (!ht_expand(table)) return NULL;
    }

    return ht_set_entry(table->entries, table->capacity, key, tableau_etats,
                        &table->length, nb_rules_by_etat);
}

/* ---------- iterator ---------- */
size_t ht_length(ht* table) {
    return table->length;
}

hti ht_iterator(ht* table) {
    hti it;
    it._table = table;
    it._index = 0;
    it.key = NULL;
    it.tableau_etats = NULL;
    it.nb_rules_by_etat = 0;
    return it;
}

bool ht_next(hti* it) {
    ht* table = it->_table;
    while (it->_index < table->capacity) {
        size_t i = it->_index++;
        if (table->entries[i].key != NULL) {
            ht_entry *entry = &table->entries[i];
            it->key = entry->key;
            it->tableau_etats = entry->tableau_etats;
            it->nb_rules_by_etat = entry->nb_rules_by_etat;
            return true;
        }
    }
    return false;
}
