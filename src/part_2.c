#include <stdio.h>
#include <stdlib.h>
#include "../headers/functions/ht.h"
#include "../headers/part_2.h"
#include "../headers/part_1.h"
#include "../headers/functions/algo.h"
#include "../headers/functions/input.h"
#include "../headers/functions/readFile.h"
#include "../headers/functions/writeFile.h"
#include "../headers/functions/modif.h"
#include "../headers/functions/test.h"
#include "../headers/functions/demo.h"
#include "../headers/functions/librairies.h"
#include "../headers/ressources.h"



void start_2(){
    int choix1, choix2, val2 = 1;

    printf("\n###################################################################################");
    printf("\n#                                                                                 #");
    printf("\n#-------------------------Bienvenue dans le mode AEF------------------------------#");
    printf("\n#                                                                                 #");
    printf("\n#  1.   Manipuler un AEF                                                          #");
    printf("\n#                                                                                 #");
    printf("\n#  Il faut tout d'abord que tu saisises differentes entrees:                      #");
    printf("\n#                                                                                 #");
    printf("\n#      - L'alphabet                                                               #");
    printf("\n#      - Les etats                                                                #");
    printf("\n#      - Les regles                                                               #");
    printf("\n#                                                                                 #");
    printf("\n#  Tu peux acceder aux parametres pour modifier le nombre d'octets afin           #");
    printf("\n#  de changer l'espace alloue pour chaque lettre/regle/etat ou longueur de saisie #");
    printf("\n#                                                                                 #");
    printf("\n#  Exemple: nb_octets = 2  => Saisie de chaque lettre sur 2 octets de l'alphabet  #");
    printf("\n#            ('a1' ou 'ab' ou 'a')                                                #");
    printf("\n#                                                                                 #");
    printf("\n###################################################################################\n\n");

    printf("\n    Saisie de l'AEF (comprenant l'alphabet et les etats):\n");
    AEF numero_1;
    do{
        printf("\nQuelle methode veux tu utiliser ?\n");
        printf("\n|Tap 1: Saisie Manuelle  ");
        printf("\n|Tap 2: Lecture Fichier  \n");
        scanf("%d", &choix1);
        switch(choix1){
            case 1:
                numero_1 = input_AEF(numero_1);
                break;
            case 2:
                numero_1 = read_file(numero_1);
                break;
            default:
                printf("\n#--------Attention choisis entre 1 et 2-------#\n");
            }
    }while(choix1 < 0 || choix1 > 2);

    printf("\n###################################################################################");
    printf("\n#                                                                                 #");
    printf("\n#  Tu vas pouvoir tester plusieurs fonctionnalites:                               #");
    printf("\n#                                                                                 #");

    while (val2 != 2){
        do{
            printf("\nQuelle manipulation voulez-vous executer? \n");
            printf("\n|Tap 1: Verifier si un mot est reconnu par l AEF");
            printf("\n|Tap 2: Verifier si un automate est complet");
            printf("\n|Tap 3: Rendre un automate complet");
            printf("\n|Tap 4: Verifier si un automate est deterministe              (pas fait)");
            printf("\n|Tap 5: Rendre l automate est deterministe                    (pas fait)");
            printf("\n|Tap 6: Verifier que tous les cycles de l AEF sont unitaires  (pas fait)");
            printf("\n|Tap 7: Extraire le langage reconnu par l AEF                 (pas fait)");
            printf("\n|Tap 8: Suppression des transitions epsilon (vides)           (pas fait)");
            printf("\n|Tap 8: Operations sur AEF:                                   (pas fait)");
            printf("\n|      - complement d un AEF");
            printf("\n|      - miroir d un AEF");
            printf("\n|      - produit de deux AEFs");
            printf("\n|      - concatenation de deux AEFs");
            printf("\n|Tap 10: Verifier si deux automates sont equivalents          (pas fait)");
            printf("\n|Tap 11: Rendre minimal un EDF deterministe                   (pas fait)");
            printf("\n|Tap 12: Modifier l AEF ");
            printf("\n|Tap 13: Sauvegarder un AEF dans un fichier du mot\n");

            
            scanf("%d", &choix2);
            switch (choix2) {
                case 1:
                    ;char * mot;
                    mot = input_mot_AEF();

                    if(verifAppartenance(&numero_1,mot)){
                        printf("Le mot que vous avez rentré appartient bien à l'AEF.\n");
                    }
                    else{
                        printf("Le mot n'appartient pas à l'AEF.\n");
                    }
                    break;
                    
                case 2:
                    if (verifComplet(&numero_1) == 0){
                        printf("\nL'automate que vous avez choisi est complet.\n");
                    }
                    else{
                        printf("\nL'automate saisi n'est pas complet.\n");
                    }
                    break;
                case 3:
                    affiche_dict(numero_1.dict_table);
                    if (verifComplet(&numero_1) == 0){
                      printf("\nL'automate est déjà complet.\n");
                    }
                    else {
                        RendreComplet(&numero_1);
                        numero_1.dict_table = dictionnary(numero_1);
                        affiche_dict(numero_1.dict_table);
                        
                        if (verifComplet(&numero_1) == 0){
                            printf("\nL'automate est maintenant complet.\n");
                        }
                        else{
                            printf("\nL'automate saisi n'est pas complet.\n");
                        }
                    }
                    break;
                case 4:
                    //verifdeterministe();
                    break;
                case 5:
                    //rendredeterministe();
                    break;
                case 6:
                    //unitaires();
                    break;
                case 12:;
                int choix3, val3 = 1;
                    while (val3 != 2){
                        do{
                            printf("\nQuelle manipulation voulez-vous executer? \n");
                            printf("\n|Tap 1: Ajouter lettre(s)");
                            printf("\n|Tap 2: Supprimer lettre");
                            printf("\n|Tap 3: Ajouter etat(s)");
                            printf("\n|Tap 4: Supprimer etat");
                            printf("\n|Tap 5: Ajouter regles(s)");
                            printf("\n|Tap 6: Supprimer regle\n");
                    
                            scanf("%d", &choix3);
                            switch (choix3) {
                                case 1:
                                    add_lettre(&numero_1);
                                    break;
                                case 2:
                                    sup_lettre(&numero_1);
                                    break;
                                case 3:
                                    add_etat(&numero_1);
                                    break;
                                case 4:
                                    sup_etat(&numero_1);
                                    break;
                                case 5:
                                    add_regle(&numero_1);
                                    break;
                                case 6:
                                    sup_regle(&numero_1);
                                    break;
                                default:
                                    printf("\nChoisissez une option.");
                                    break;
                            }
                        }while(choix3 < 0 || choix3 > 14);
                        
                        printf("\nVoulez vous faire une autre manip ou recommencer ? ");
                        printf("\nOUI : 1 / NON : 2\n");
                        scanf("%d", &val3);
                    }
                                
                    break;
                case 13:
                    save_file(numero_1);
                    break;

                default:
                    printf("\nChoisissez une option.");
                    break;
            }
        }while(choix1 < 0 || choix1 > 14);

        printf("\nVoulez vous faire une autre manip ou recommencer ? ");
        printf("\nOUI : 1 / NON : 2\n");
        scanf("%d", &val2);
    }
}

AEF input_AEF(AEF aef){
    int i;
    printf("Saisir le nombre de lettres contenues dans l'alphabet de l'AEF \n");
    scanf("%d",&aef.nb_letters);

    alphabet_verif = malloc(aef.nb_letters * sizeof(malloc(nb_octets * sizeof(char))));

    aef.alphabet = input_alphabet(aef.nb_letters, 0);
    for (i = 0; i < aef.nb_letters; i++)  printf("alphabet n %d: %s \n",i, aef.alphabet[i]); //print des regles

    printf("\nSaisir le nombre d etats de l AEF: ");
    scanf("%d",&aef.nb_etats);
    
    printf("\nSaisir le nombre d etats de depart: ");
    scanf("%d",&aef.nb_etats_init);

    printf("\nSaisir le nombre d etats d arrivee: ");
    scanf("%d",&aef.nb_etats_end);
    getchar();

    aef.etats = input_etat(aef.nb_etats, aef.alphabet, aef.nb_etats_init, aef.nb_etats_end, aef.nb_letters);
    aef.liste_a_comparer = malloc((aef.nb_letters + aef.nb_etats) * sizeof(malloc(nb_octets * sizeof(char))));
    for (int i = 0; i < aef.nb_letters + aef.nb_etats;i++){
        if (i <aef.nb_letters) aef.liste_a_comparer[i] = aef.alphabet[i];
        else aef.liste_a_comparer[i] = aef.etats[0][i-aef.nb_letters];
    }

    printf("\nSaisir le nombre de regles(transitions) de l AEF: ");
    scanf("%d",&aef.nb_regles);

    affiche_alphabet(&aef);
    affiche_etats(&aef);

    getchar();
    
    //NUMERO 3.1
    //regles_normal = malloc(3 * sizeof(malloc(nb_octets * sizeof(char))));
    //NUMERO 4.1
    //regles_verif = malloc(aef.nb_regles *sizeof(malloc(3*nb_octets * sizeof(char)+2 )));
    
    affiche_liste_compare(&aef);
    aef.regles = input_regle(aef);

    aef.dict_table  = dictionnary(aef);
    affiche_dict(aef.dict_table);

    return aef;

}
