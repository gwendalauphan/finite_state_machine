#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../headers/functions/ht.h"
#include "../../headers/part_2.h"
#include "../../headers/ressources.h"

/* Petite aide pour sortir proprement en cas d'OOM */
static void exit_nomem(void) {
    fprintf(stderr, "out of memory\n");
    exit(EXIT_FAILURE);
}

/* Libère un tableau tab[nb][2] de char* */
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

/*
 * Construit un "dictionnaire" : pour chaque état, associe la liste de ses transitions (symbole, état_d'arrivée).
 * Hypothèse sur aef.regles[j]: {source, symbole, destination}
 */
ht* dictionnary(AEF aef) {
    ht *counts = ht_create(aef.nb_etats);  // table de hachage: clé = état, valeur = char*** transitions
    if (!counts) exit_nomem();

    for (int i = 0; i < aef.nb_etats; i++) {
        const char *etat = aef.etats[0][i];
        if (!etat) continue;

        // Si déjà présent, on saute (évite double insertion)
        if (ht_get(counts, etat) != NULL) {
            // fprintf(stderr, "État déjà présent dans le dictionnaire: %s\n", etat);
            continue;
        }

        // 1) Compter le nombre de règles sortantes pour cet état
        int nb_rules = 0;
        for (int j = 0; j < aef.nb_regles; j++) {
            if (aef.regles[j][0] && strcmp(aef.regles[j][0], etat) == 0) {
                nb_rules++;
            }
        }

        // 2) Allouer et remplir le tableau de règles
        char ***tab = NULL;
        int nb_entries = 0;

        if (nb_rules == 0) {
            // Pas de transition sortante -> on stocke un marqueur "~"
            nb_entries = 1;
            tab = (char ***)calloc((size_t)nb_entries, sizeof(char **));
            if (!tab) exit_nomem();
            tab[0] = (char **)calloc(2, sizeof(char *));
            if (!tab[0]) { free(tab); exit_nomem(); }

            tab[0][0] = strdup("~");
            tab[0][1] = strdup("~");
            if (!tab[0][0] || !tab[0][1]) exit_nomem();
        } else {
            nb_entries = nb_rules;
            tab = (char ***)calloc((size_t)nb_entries, sizeof(char **));
            if (!tab) exit_nomem();

            int k = 0;
            for (int j = 0; j < aef.nb_regles; j++) {
                if (aef.regles[j][0] && strcmp(aef.regles[j][0], etat) == 0) {
                    tab[k] = (char **)calloc(2, sizeof(char *));
                    if (!tab[k]) { free_rules_table(tab, k); exit_nomem(); }

                    // On duplique les chaînes pour éviter d’écraser/voler la mémoire de aef
                    const char *symb = aef.regles[j][1] ? aef.regles[j][1] : "";
                    const char *dest = aef.regles[j][2] ? aef.regles[j][2] : "";

                    tab[k][0] = strdup(symb);
                    tab[k][1] = strdup(dest);
                    if (!tab[k][0] || !tab[k][1]) { free_rules_table(tab, k+1); exit_nomem(); }
                    k++;
                }
            }
        }

        // 3) Insertion dans la HT (API existante dans ton code)
        if (ht_set_entry(counts->entries,
                         counts->capacity,
                         etat,
                         tab,
                         &counts->length,
                         nb_entries) == NULL) {
            // si insertion échoue, libérer tab pour éviter fuite
            free_rules_table(tab, nb_entries);
            exit_nomem();
        }

        // (tab appartient désormais à la HT; destruction à faire dans ht_destroy)
    }

    // printf("Enregistrement fini\n");
    return counts;
}
