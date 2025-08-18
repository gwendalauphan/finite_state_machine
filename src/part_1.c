#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/part_1.h"
#include "../headers/part_2.h"
#include "../headers/functions/algo.h"
#include "../headers/functions/input.h"
#include "../headers/functions/librairies.h"
#include "../headers/functions/modif.h"
#include "../headers/functions/test.h"
#include "../headers/settings.h"
#include "../headers/ressources.h"


void start_1(){
    int choix2, val2 = 1;
    printf("\n###################################################################################");
    printf("\n#                                                                                 #");
    printf("\n#-------------------------Bienvenue dans le mode Alphabet-------------------------#");
    printf("\n#                                                                                 #");
    printf("\n#  1.   Manipuler des mots d un alphabet                                          #");
    printf("\n#                                                                                 #");
    printf("\n#  Il faut tout d'abord que tu saisises differentes entrees:                      #");
    printf("\n#                                                                                 #");
    printf("\n#      - L'alphabet                                                               #");
    printf("\n#      - Le mot                                                                   #");
    printf("\n#                                                                                 #");
    printf("\n#  Tu peux acceder aux parametres pour modifier le nombre d'octets afin           #");
    printf("\n#  de changer l'espace alloue pour chaque lettre/regle/etat ou longueur de saisie #");
    printf("\n#                                                                                 #");
    printf("\n#  Exemple: nb_octets = 2  => Saisie de chaque lettre sur 2 octets de l'alphabet  #");
    printf("\n#            ('a1' ou 'ab' ou 'a')                                                #");
    printf("\n#                                                                                 #");
    printf("\n###################################################################################\n\n");


    printf("\n###################################################################################");
    printf("\n#                                                                                 #");
    printf("\n#  Tu vas pouvoir tester plusieurs fonctionnalites:                               #");
    printf("\n#                                                                                 #");
    Alpha_Mot numero_1;
    numero_1 = input_Alpha_Mot(numero_1);

    while (val2 != 2){
        do{
            printf("\nQuelle manipulation voulez-vous executer? \n");
            printf("\n|Tap 1: Verifier si le mot appartient l'alphabet. ");
            printf("\n|Tap 2: Puissance du mot.");
            printf("\n|Tap 3: Verfier si le mot est vide");
            printf("\n|Tap 4: Concatener des mots");
            printf("\n|Tap 5: Miroir du mot");
            printf("\n|Tap 6: Savoir si le mot est fini");
            printf("\n|Tap 7: Changer de mot\n");

            scanf("%d", &choix2);
            switch (choix2) {
                case 1:
                    if (mot_appatient_alpha(&numero_1) == 0){
                        printf("Le mot appartient bien a l'alphabet\n");
                    }
                    else {
                        printf("\nLe mot n'appartient pas à l'alphabet.\n");
                    }
                    break;
                case 2:
                    puissance_mot(&numero_1);
                    break;
                case 3:
                    mot_vide();
                    break;
                case 4:
                    concatenation(&numero_1);
                    break;
                case 5:
                    miroir(&numero_1);
                    break;
                case 6:
                    estEnd(&numero_1);
                    break;
                case 7:
                    input_mot(&numero_1);
                    break;

                default:
                    printf("\nChoisissez une option.");
                    break;
                }

            }while(choix2 < 0 || choix2 > 8);

        printf("\nVoulez vous faire une autre manip ou recommencer ? ");
        printf("\nOUI : 1 / NON : 2\n");
        scanf("%d", &val2);
    }
}

Alpha_Mot input_Alpha_Mot(Alpha_Mot alpha_mot){
    int i;
    printf("\nSaisir le nombre de lettres contenues dans l'alphabet\n");
    scanf("%d",&alpha_mot.nb_letters_alpha);

    printf("\nSaisie de l'alphabet:\n");
    alphabet_verif = malloc(alpha_mot.nb_letters_alpha * sizeof(malloc(nb_octets * sizeof(char))));
    alpha_mot.alphabet = input_alphabet(alpha_mot.nb_letters_alpha, 0);

    printf("Saisir le nombre de lettres contenues dans le mot\n");
    printf("(Et non le nombre d'octets contenues dans le mot)\n");
    scanf("%d",&alpha_mot.nb_letters_mot);


    alpha_mot.mot = malloc(nb_octets*alpha_mot.nb_letters_mot * sizeof(char));
    printf("\nSaisie du mot: \n");
    scanf("%s",alpha_mot.mot);

    printf("print de l'alphabet:\n");
    for(i = 0; i<alpha_mot.nb_letters_alpha;i++){
        printf("lettre: %s\n",alpha_mot.alphabet[i]);
    }
    printf("print du mot: %s\n", alpha_mot.mot);

    return alpha_mot;

}
