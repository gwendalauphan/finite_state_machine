#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../headers/functions/ht.h"
#include "../../headers/part_1.h"
#include "../../headers/part_2.h"
#include "../../headers/functions/librairies.h"
#include "../../headers/ressources.h"

int mot_appatient_alpha(Alpha_Mot* alpha_mot){
        int i,j;
        char tmp[nb_octets];
        for(i=0; i<alpha_mot->nb_letters_mot*nb_octets;i+=nb_octets){
                for(j = 0; j<nb_octets;j++){
                        tmp[j]= alpha_mot->mot[j+i];
                }
                tmp[nb_octets] = '\0';
                if (verif_element_in_tab_2D(alpha_mot->alphabet,alpha_mot->nb_letters_alpha,tmp)==1){
                        return 1;
                        break;
                }
        }
        return 0;
}

void mot_vide(){
        printf("\nLe mot ne peut pas être vide car il y a une vérification \n de sa longueur au moment de la saisie\n");
}


void concatenation(Alpha_Mot* alpha_mot){
        int i,nb_lettres;
        char *mot_concat;
        char *mot_saisie;
        printf("\nSaisissez la longueur du mot a concatener: ");
        scanf("%d",&nb_lettres);
        mot_concat = malloc(nb_octets*alpha_mot->nb_letters_mot * sizeof(char));
        strcpy(mot_concat, alpha_mot->mot);
        mot_concat = realloc(mot_concat,nb_octets*(nb_lettres + alpha_mot->nb_letters_mot) * sizeof(char));
        mot_saisie = malloc(nb_octets*nb_lettres * sizeof(char));
        printf("\nSaisie du mot: \n");
        scanf("%s", mot_saisie);
        for (i = 0; i<nb_lettres; i++){
               mot_concat[alpha_mot->nb_letters_mot+i] = mot_saisie[i];
        }
        printf("Mot concatene: %s\n", mot_concat);
}

void miroir(Alpha_Mot* alpha_mot){
        char *mot_miroir;
        mot_miroir = malloc(nb_octets*alpha_mot->nb_letters_mot * sizeof(char));
        for (int i = 0; i<alpha_mot->nb_letters_mot; i++){
                mot_miroir[i] = alpha_mot->mot[alpha_mot->nb_letters_mot-i-1];
        }
        mot_miroir[alpha_mot->nb_letters_mot] = '\0';
        printf("Mot miroir: %s\n", mot_miroir);
}

void estEnd(Alpha_Mot* alpha_mot){
        printf("\nLe mot est forcement fini car on ne peut pas saisir \n d expressions regulieres lors de la saisie de mot\n");
}

int verifAppartenanceRecursive(AEF *aef, char *mot, char * etat_actuel, int profondeur){
        for (int j = 0; j < aef->nb_regles;j++){
                char tmp[nb_octets];
                for (int i =0; i < nb_octets; i ++){
                        tmp[i] = mot[profondeur*nb_octets];
                }
                tmp[nb_octets] = '\0';
                
                if (!strcmp(aef->regles[j][0], etat_actuel) && !strcmp(aef->regles[j][1], tmp)){
                        if (strlen(mot)/nb_octets == profondeur+1){
                                int estFinal = 0;
                                for (int i = 0; i < aef->nb_etats_end; i ++){
                                        if (!strcmp(aef->regles[j][2], aef->etats[2][i])) estFinal = 1;
                                }
                                return estFinal;
                        }
                        else{
                                printf("\n");
                                return verifAppartenanceRecursive(aef, mot, aef->regles[j][2], profondeur+1);
                        }
                }
        }
        return 0;
}

int verifAppartenance (AEF* aef,char *mot){
        int count = 0;
        for (int i = 0; i < aef->nb_etats_init; i ++){
                count += verifAppartenanceRecursive(aef, mot, aef->etats[1][i], 0);
        }

        return (count > 0);
}

static int contains_symbol_in_rules(ht_entry *e, const char *sym) {
    for (int k = 0; k < e->nb_rules_by_etat; k++) {
        if (strcmp(e->tableau_etats[k][0], sym) == 0) return 1;
    }
    return 0;
}

int verifComplet(AEF* aef){
    for (int i = 0; i < aef->nb_etats; i++){
        ht_entry *e = ht_get(aef->dict_table, aef->etats[0][i]);
        if (!e) return 1;
        for (int j = 0; j < aef->nb_letters; j++){
            if (!contains_symbol_in_rules(e, aef->alphabet[j])) {
                return 1; // missing transition
            }
        }
    }
    return 0;
}

