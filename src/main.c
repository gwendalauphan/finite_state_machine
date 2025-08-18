#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../headers/ressources.h"
#include "../headers/part_1.h"
#include "../headers/part_2.h"
#include "../headers/part_3.h"
#include "../headers/settings.h"



int main(int argc, char **argv) {

    int choix, val = 1;
    alphabet_verif = malloc(1 * sizeof(malloc(nb_octets * sizeof(char))));
    afficherOctets();

    while (val != 2){
        do{
            printf("\nQuel mode veux tu executer ?");
            printf("\n|Tap 1: Manipuler des mots d un alphabet ");
            printf("\n|Tap 2: Manipuler un AEF");
            printf("\n|Tap 3: Expressions regulieres (Ers)  (pas fait)\n");

            scanf("%d", &choix);
            switch(choix)
            {
                case 1:
                    start_1();
                    break;
                case 2:
                    start_2();
                    break;
                case 3:
                    start_3();
                    break;
                default:
                    printf("\n#--------Attention choisis entre 1 et 3-------#\n");
                    
            }
            
        }while(choix < 0 || choix > 4);

        printf("\nVeux tu faire un autre mode ou recommencer ? ");
        printf("\nOUI : 1 / NON : 2\n");
        scanf("%d", &val);
        }

	return 0;
}
