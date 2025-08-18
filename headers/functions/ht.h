// Simple hash table implemented in C.
#ifndef _HT_H
#define _HT_H

#include <stdbool.h>
#include <stddef.h>

/* --- Types --- */

typedef struct ht_entry {
    const char *key;        // NULL si case vide (clé dupliquée via strdup)
    int nb_rules_by_etat;   // nombre d’entrées dans tableau_etats
    char ***tableau_etats;  // transitions: tab[nb][2] -> {symbole, destination}
} ht_entry;

typedef struct ht {
    ht_entry *entries;  // slots de la table
    size_t capacity;    // taille de entries (puissance de 2, gérée en .c)
    size_t length;      // nombre d’éléments insérés
} ht;

/* --- API --- */

// Crée une table; renvoie NULL en cas d’OOM.
// La capacité interne est arrondie à la puissance de 2 >= initial_capacity.
ht *ht_create(int initial_capacity);

// Libère la table, y compris chaque clé dupliquée et chaque valeur tableau_etats.
void ht_destroy(ht *table);

// Récupère l’entrée associée à key, ou NULL si absente.
ht_entry *ht_get(ht *table, const char *key);

// Insère/remplace la valeur pour key.
// key est dupliquée; tableau_etats ne doit pas être NULL.
// Retourne le pointeur vers la clé stockée (dupliquée) ou NULL en cas d’échec.
const char *ht_set(ht *table, const char *key, char ***tableau_etats, int nb_rules_by_etat);

// Nombre d’éléments stockés.
size_t ht_length(ht *table);

/* --- Itérateur --- */

typedef struct {
    const char *key;          // clé courante
    char ***tableau_etats;    // valeur courante
    int nb_rules_by_etat;     // taille de tableau_etats
    // Champs internes — ne pas utiliser
    ht *_table;
    size_t _index;
} hti;

// Crée un itérateur.
hti ht_iterator(ht *table);

// Avance l’itérateur; renvoie true si un élément est dispo et met
// à jour key/tableau_etats/nb_rules_by_etat, sinon false.
bool ht_next(hti *it);

#endif // _HT_H
