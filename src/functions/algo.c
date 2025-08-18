#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../headers/functions/ht.h"
#include "../../headers/part_1.h"
#include "../../headers/part_2.h"
#include "../../headers/ressources.h"
#include "../../headers/functions/modif.h"
#include "../../headers/functions/librairies.h"


// Multiply a word by a given power and print the result
void puissance_mot(Alpha_Mot* alpha_mot) {
    int i, taille_mot, nb;
    printf("\nSaisissez la puissance a laquelle le mot doit etre multiplie\n");
    scanf("%d", &nb);

    if (nb <= 0) {
        printf("La puissance doit etre positive.\n");
        return;
    }

    taille_mot = alpha_mot->nb_letters_mot * nb_octets * nb;
    char *mot_return = malloc((taille_mot + 1) * sizeof(char)); // +1 for '\0'
    if (!mot_return) {
        fprintf(stderr, "Erreur d'allocation memoire.\n");
        return;
    }

    for (i = 0; i < taille_mot; i++) {
        mot_return[i] = alpha_mot->mot[i % (alpha_mot->nb_letters_mot * nb_octets)];
    }
    mot_return[taille_mot] = '\0';

    printf("Mot puissance %d: %s\n", nb, mot_return);
    free(mot_return);
}

void RendreComplet(AEF* aef) {
    if (!aef || !aef->dict_table) {
        fprintf(stderr, "AEF invalide.\n");
        return;
    }

    printf("\nRendre complet l'AEF\n");

    // 1) Construire le nom de l'état puits: "&&&...&" (nb_octets fois) + '\0'
    char *sink = malloc((size_t)nb_octets + 1);
    if (!sink) { fprintf(stderr, "OOM\n"); return; }
    for (int w = 0; w < nb_octets; w++) sink[w] = '&';
    sink[nb_octets] = '\0';

    // Vérifier si l'état puits existe déjà
    bool sink_exists = false;
    for (int i = 0; i < aef->nb_etats; i++) {
        if (strcmp(aef->etats[0][i], sink) == 0) { sink_exists = true; break; }
    }

    // 2) Pour chaque état, s'assurer qu'il y a une transition sortante par symbole
    for (int i = 0; i < aef->nb_etats; i++) {
        const char *etat = aef->etats[0][i];
        ht_entry *e = ht_get(aef->dict_table, etat);
        if (!e) {
            // Pas d'entrée dans le dict → on ajoutera tout vers le puits
            for (int j = 0; j < aef->nb_letters; j++) {
                char *rule[3] = { (char*)etat, aef->alphabet[j], sink };
                ajout_regle(aef, rule);
            }
            continue;
        }

        // Cas particulier: "0 règle" encodée par placeholder "~"
        bool has_placeholder_zero = (e->nb_rules_by_etat == 1 &&
                                     e->tableau_etats &&
                                     e->tableau_etats[0] &&
                                     e->tableau_etats[0][0] &&
                                     strcmp(e->tableau_etats[0][0], "~") == 0);

        for (int j = 0; j < aef->nb_letters; j++) {
            int count_letter = 0;

            if (!has_placeholder_zero) {
                for (int k = 0; k < e->nb_rules_by_etat; k++) {
                    if (e->tableau_etats[k] && e->tableau_etats[k][0] &&
                        strcmp(aef->alphabet[j], e->tableau_etats[k][0]) == 0) {
                        count_letter++;
                        break;
                    }
                }
            }

            if (count_letter == 0) {
                char *rule[3] = { (char*)etat, aef->alphabet[j], sink };
                ajout_regle(aef, rule);
            }
        }
    }

    // 3) Ajouter l'état puits s'il n'existait pas encore
    if (!sink_exists) {
        // +1 place pour le nouvel état
        char **new_states = realloc(aef->etats[0], (size_t)(aef->nb_etats + 1) * sizeof(*aef->etats[0]));
        if (!new_states) { fprintf(stderr, "OOM\n"); free(sink); return; }
        aef->etats[0] = new_states;
        aef->etats[0][aef->nb_etats] = sink; // ownership transféré
        aef->nb_etats++;
    } else {
        // si déjà présent, on n’a pas besoin de garder ce malloc local
        free(sink);
        // retrouver le pointeur officiel du puits
        for (int i = 0; i < aef->nb_etats; i++) {
            if (strcmp(aef->etats[0][i], sink) == 0) {
                sink = aef->etats[0][i];
                break;
            }
        }
    }

    // 4) Boucles du puits sur tout l’alphabet
    for (int i = 0; i < aef->nb_letters; i++) {
        char *rule[3] = { sink, aef->alphabet[i], sink };
        ajout_regle(aef, rule);
    }

    printf("\nFin de l'algo RendreComplet\n");
}
