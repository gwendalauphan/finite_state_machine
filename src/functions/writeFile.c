#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../headers/ressources.h"
#include "../../headers/part_2.h"

void save_file(AEF aef){
    FILE *file = fopen("data/saveAEF.txt", "w");

    fprintf(file, "nombre_octet %d\n", nb_octets);
    
    fprintf(file, "alphabet ");
    for (int i = 0; i < aef.nb_letters; i++){
        fprintf(file, "%s", aef.alphabet[i]);

        if (i != aef.nb_letters-1) fprintf(file, "-");
    }

    fprintf(file, "\nregles ");
    for (int i = 0; i < aef.nb_regles; i++){
        fprintf(file, "%s,%s,%s", aef.regles[i][0], aef.regles[i][1], aef.regles[i][2]);

        if (i != aef.nb_regles-1) fprintf(file, "-");
    }

    fprintf(file, "\netats ");
    for (int i = 0; i < aef.nb_etats; i++){
        fprintf(file, "%s", aef.etats[0][i]);

        if (i != aef.nb_etats-1) fprintf(file, "-");
    }

    fprintf(file, "\netat_initiaux ");
    for (int i = 0; i < aef.nb_etats_init; i++){
        fprintf(file, "%s", aef.etats[1][i]);

        if (i != aef.nb_etats_init-1) fprintf(file, "-");
    }

    fprintf(file, "\netat_finaux ");
    for (int i = 0; i < aef.nb_etats_end; i++){
        fprintf(file, "%s", aef.etats[2][i]);

        if (i != aef.nb_etats_end-1) fprintf(file, "-");
    }

    fclose(file);

    printf("\nAEF bien sauvegardé \n");

}