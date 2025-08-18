#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../headers/part_1.h"
#include "../../headers/part_2.h"
#include "../../headers/ressources.h"
#include "../../headers/functions/input.h"
#include "../../headers/functions/librairies.h"

void ajout_lettre(AEF* aef, char**alphabet_to_add, int nb_lettres_to_add){
    int i;
    aef->nb_letters+= nb_lettres_to_add;

    aef->alphabet = realloc(aef->alphabet,aef->nb_letters*sizeof(char*));
    for (i = aef->nb_letters-nb_lettres_to_add; i<aef->nb_letters; i++){
        aef->alphabet[i] = alphabet_to_add[i+nb_lettres_to_add-aef->nb_letters];
    }

    for (i = 0; i < aef->nb_letters + aef->nb_etats;i++){
        if (i <aef->nb_letters) aef->liste_a_comparer[i] = aef->alphabet[i];
        else aef->liste_a_comparer[i] = aef->etats[0][i-aef->nb_letters];
    }

    affiche_alphabet(aef);
}

void add_lettre(AEF* aef){
    int nb_lettres_to_add,i;
    char **alphabet_to_add;

    affiche_alphabet(aef);
    affiche_etats(aef);

    printf("Combien de lettre(s) voulez vous ajouter ?\n");
    scanf("%d",&nb_lettres_to_add);
    alphabet_to_add = malloc(nb_lettres_to_add*sizeof(char*));

    if (alphabet_verif == NULL) alphabet_verif = malloc((aef->nb_letters+aef->nb_etats) * sizeof(malloc(nb_octets * sizeof(char))));
    else alphabet_verif = realloc(alphabet_verif,(aef->nb_letters+aef->nb_etats) * sizeof(malloc(nb_octets * sizeof(char))));
    alphabet_verif = aef->liste_a_comparer;
    for(i=0; i<aef->nb_letters+aef->nb_etats; i++){
        printf("alphabet_verif depuis modif lettre: %s\n", alphabet_verif[i]);
    }

    alphabet_to_add = input_alphabet(nb_lettres_to_add, aef->nb_letters+aef->nb_etats);
    ajout_lettre(aef, alphabet_to_add, nb_lettres_to_add);
    

    //free a faire
}

void sup_lettre(AEF* aef){
    char *lettre;
    int i,val;
    affiche_alphabet(aef);
    printf("\nQuelle lettre voulez vous supprimer ?  \n");
    getchar();
    lettre = read_input_letter(nb_octets,0,0);
    for(i = 0; i<aef->nb_letters;i++){
        if(strcmp(lettre, aef->alphabet[i])==0){
            val = sup_check_regle(lettre, aef, 0);
            if (val==0){
                sup_regle_by_lettre(lettre, aef, 0);
                sup_let_in_alpha(lettre, aef);
                continue;
            }
            else if(val == 2){
                printf("2");
                sup_let_in_alpha(lettre, aef);
            }
        }
    }
    for (i = 0; i < aef->nb_letters + aef->nb_etats;i++){
        if (i <aef->nb_letters) aef->liste_a_comparer[i] = aef->alphabet[i];
        else aef->liste_a_comparer[i] = aef->etats[0][i-aef->nb_letters];
    }
    affiche_alphabet(aef);
    affiche_regles(aef);

}

void ajout_etat(AEF* aef, char **etat_to_add, int nb_etats_to_add){
    int i;
    aef->nb_etats+= nb_etats_to_add;

    aef->etats[0] = realloc(aef->etats[0],aef->nb_etats*sizeof(char*));
    for (i = aef->nb_etats-nb_etats_to_add; i<aef->nb_etats; i++){
        aef->etats[0][i] =  etat_to_add[i+nb_etats_to_add-aef->nb_etats];
    }

    for (i = 0; i < aef->nb_letters + aef->nb_etats;i++){
        if (i <aef->nb_letters) aef->liste_a_comparer[i] = aef->alphabet[i];
        else aef->liste_a_comparer[i] = aef->etats[0][i-aef->nb_letters];
    }


    affiche_etats(aef);
}

void add_etat(AEF* aef){
    int nb_etats_to_add;
    char **etat_to_add;

    affiche_alphabet(aef);
    affiche_etats(aef);

    printf("Combien d'etat(s) voulez vous ajouter ?");
    scanf("%d",&nb_etats_to_add);
    etat_to_add = malloc(nb_etats_to_add*sizeof(char*));

    alphabet_verif = aef->liste_a_comparer;
    getchar();

    etat_to_add = read_input_etats(nb_octets,aef->nb_etats+aef->nb_letters,nb_etats_to_add,aef->etats[0],aef->nb_etats);
    ajout_etat(aef, etat_to_add, nb_etats_to_add);

    //free a faire
}

void sup_etat(AEF* aef){
    char *etat;
    int i,val;
    affiche_etats(aef);
    printf("\nQuelle etat voulez vous supprimer ?  \n");
    getchar();
    etat = read_input_letter(nb_octets,0,0);
    for(i = 0; i<aef->nb_etats;i++){
        if(strcmp(etat, aef->etats[0][i])==0){
            val = sup_check_regle(etat, aef, 1);
            if (val==0){
                sup_regle_by_lettre(etat, aef, 1);
                sup_etat_in_etats(etat, aef); // LA aussi
                sup_etat_in_etats_initiaux(etat, aef); // LA aussi
                sup_etat_in_etats_finaux(etat, aef); // LA aussi
                continue;
            }
            else if(val == 2){
                printf("2");
                sup_etat_in_etats(etat, aef); // LA aussi
                sup_etat_in_etats_initiaux(etat, aef); // LA aussi
                sup_etat_in_etats_finaux(etat, aef); // LA aussi
            }
        }
    }
    for (i = 0; i < aef->nb_letters + aef->nb_etats;i++){
        if (i <aef->nb_letters) aef->liste_a_comparer[i] = aef->alphabet[i];
        else aef->liste_a_comparer[i] = aef->etats[0][i-aef->nb_letters];
    }
    affiche_alphabet(aef);
    affiche_etats(aef);
    affiche_regles(aef);

}

void ajout_regle(AEF *aef, char **regle_to_add){
    aef->nb_regles+= 1;
    aef->regles = realloc(aef->regles,aef->nb_regles*sizeof(char**));
    aef->regles[aef->nb_regles-1] = malloc(3*sizeof(char*));

    aef->regles[aef->nb_regles-1][0] =  regle_to_add[0];
    aef->regles[aef->nb_regles-1][1] =  regle_to_add[1];
    aef->regles[aef->nb_regles-1][2] =  regle_to_add[2];

    affiche_regles(aef);
}

void add_regle(AEF* aef){
    affiche_regles(aef);

    int nb_regle_to_add;
    printf("Combien de rêgles voulez vous ajouter ?\n");
    scanf("%d", &nb_regle_to_add);
    char **regle_to_add;
    regle_to_add = malloc(nb_regle_to_add*sizeof(char*));
    //regles_verif = realloc(regles_verif,(aef->nb_regles+nb_regle_to_add) *sizeof(malloc(3*nb_octets * sizeof(char)+2 )));
    regles_verif = malloc((aef->nb_regles+nb_regle_to_add) * sizeof(char*));
    for (int i = 0; i < aef->nb_regles+nb_regle_to_add; i++){
        regles_verif[i] = malloc((nb_octets*3+2)*sizeof(char));
    }

    for (int i = 0; i < aef->nb_regles; i ++){
        sprintf(regles_verif[i], "%s-%s-%s", aef->regles[i][0], aef->regles[i][1], aef->regles[i][2]);
    }

    getchar();
    for (int i = 0; i < nb_regle_to_add; i ++){
        regle_to_add = read_input_regle(nb_octets, aef->liste_a_comparer,aef->nb_etats,aef->nb_letters, aef->nb_regles);
        ajout_regle(aef, regle_to_add);
    }
}

void sup_regle(AEF* aef){
    char **regle_to_sup;
    affiche_regles(aef);
    printf("\nQuelle regle voulez vous supprimer ?  \n");
    getchar();
    regle_to_sup = read_input_regle(nb_octets, aef->liste_a_comparer,aef->nb_etats,aef->nb_letters, 0);
    sup_regle_by_regle(regle_to_sup, aef);

    affiche_alphabet(aef);
    affiche_etats(aef);
    affiche_regles(aef);

}



