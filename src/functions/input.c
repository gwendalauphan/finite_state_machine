#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../headers/part_1.h"
#include "../../headers/part_2.h"
#include "../../headers/functions/ht.h"
#include "../../headers/ressources.h"
#include "../../headers/functions/librairies.h"


char **input_alphabet(int nb_letters, int index){

    int tmp;                // EN Fonction de l'index
        if (index !=0) {    // On met a jour tmp 
        tmp = index;        // Qui est l index actif dans alphabet_verif
    }
    else {
        tmp = nb_letters;
    }
    alphabet_verif = realloc(alphabet_verif,tmp * sizeof(malloc(nb_octets * sizeof(char))));
    //alphabet_verif = malloc(tmp * sizeof(malloc(nb_octets * sizeof(char))));
    /*
    for(int i=0; i<tmp; i++){
        printf("alphabet_verif depuis input : %s\n", alphabet_verif[i]);
    }
    */
    int i;
    char **alphabet;
    alphabet = malloc(nb_letters * sizeof(malloc(nb_octets * sizeof(char))));
    getchar();

    for(i=0; i < nb_letters; i++){
        alphabet[i] = read_input_letter(nb_octets,index + i,0);
    }

    return alphabet;
}

char ***input_etat(int nb_etats, char **alphabet, int nb_etats_init, int nb_etats_end, int nb_letters)
{
    int i,j;
    char ***etats;
    etats = malloc(3*sizeof(char**));
    if (etats == NULL)
    {
        printf("Échec de l'allocation n°1\n");
        return NULL;
    }

    for (i=0 ; i<3 ; i++) {
        etats[i] = malloc(nb_etats*sizeof(char*));  //Allocation

        if (etats[i] == NULL)
        {
            printf("Échec de l'allocation n°2\n");
            return NULL;
        }
    }
    for (i=0 ; i<3 ; i++){
        for (j=0 ; j<nb_etats ; j++){
            etats[i][j] = malloc(nb_octets*sizeof(char));
            if (etats[i][j] == NULL)
            {
                printf("Échec de l'allocation n°3\n");
                return NULL;
            }
        }
    }
    printf("\nSaisie des etat(s)\n");
    etats[0] = read_input_etats(nb_octets, 0, nb_etats, alphabet, nb_letters);
    printf("\nSaisie des etat(s) initial(aux)\n");
    etats[1] = read_input_etats(nb_octets, 1, nb_etats_init, etats[0], nb_etats);
    printf("\nSaisie des etat(s) final(aux)\n");
    etats[2] = read_input_etats(nb_octets, 1, nb_etats_end, etats[0], nb_etats);

    return etats;
} 

char ***input_regle(AEF aef)
{   
    regles_verif = malloc(aef.nb_regles*sizeof(malloc(3*nb_octets * sizeof(char)+2 )));
    //TABLEAU EN 3 DIMENSIONS
    //DIM 1 = nb_rules  (En colonne (y))
    //DIM 2 = 3   (nb elements dans une regle)(En ligne(x))
    //DIM 3 = nb_octets (En profondeur (z))


    int i,j;
    char ***return_AEF;
    return_AEF = malloc(aef.nb_regles * sizeof(char **));
    if (return_AEF == NULL)
    {
        printf("Échec de l'allocation n°1\n");
        return NULL;
    }

    for (int i=0 ; i<aef.nb_regles; i++) {
        return_AEF[i] = malloc(3*sizeof(char*));  //Allocation

        if (return_AEF[i] == NULL)
        {
            printf("Échec de l'allocation n°2\n");
            return NULL;
        }
    }
    for (i=0 ; i<aef.nb_regles ; i++){
        for (j=0 ; j<3 ; j++){
            return_AEF[i][j] = malloc(nb_octets*sizeof(char));
            if (return_AEF[i][j] == NULL)
            {
                printf("Échec de l'allocation n°3\n");
                return NULL;    
            }
        }
    }
    printf("\nSaisie des regles (FORMAT): etat-lettre-etat\n\n");
    for (i = 0; i < aef.nb_regles; i++)
    {
        return_AEF[i] = read_input_regle(nb_octets, aef.liste_a_comparer, aef.nb_etats,aef.nb_letters,i);
    }

        //Verif sur au moins 1 regle avec depart
        //Verif sur au moins 1 regle avec arrivee

    return return_AEF;
}

void input_mot(Alpha_Mot * alpha_mot){
    printf("Saisir le nombre de lettres contenues dans le mot\n");
    printf("(Et non le nombre d'octets contenues dans le mot)\n");
    scanf("%d",&alpha_mot->nb_letters_mot);

    alpha_mot->mot = malloc(nb_octets*alpha_mot->nb_letters_mot * sizeof(char));

    printf("\nSaisie du mot: \n");
    scanf("%s", alpha_mot->mot);

    printf("print du mot: %s\n", alpha_mot->mot);
}

char *input_mot_AEF(){
    char * mot;
    int nb_letters_mot;
    printf("Saisir le nombre de lettres contenues dans le mot\n");
    printf("(Et non le nombre d'octets contenues dans le mot)\n");
    scanf("%d",&nb_letters_mot);

    mot = malloc(nb_octets*nb_letters_mot * sizeof(char));
    printf("\nSaisie du mot: \n");
    scanf("%s", mot);
    printf("print du mot: %s\n", mot);
    
    return mot;
}