#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../headers/part_2.h"
#include "../../headers/part_1.h"
#include "../../headers/ressources.h"
#include "../../headers/functions/input.h"

char *read_input_letter(int longueur, int index, int status)
{
    int i,c, essai = 0, val1, status_bis;
    char longueurStr[12]; // Enough for int as string
    
    char *chaine_verif = malloc((longueur + 1) * sizeof(char)); //Variable qui enregistre notre saisie

    char *saisie = malloc((longueur + 1) * sizeof(char)); //Variable qu'on retourne apres verif

    const char *phrase_mod[3]; //Variable servant à un print

    //######-------Code servant à initialiser les valeurs acceptees du scanf----#####

    char str_taille[14];
    char lettre_acceptee[11] = "[a-zA-Z0-9-";
    sprintf(longueurStr, "%d", longueur);
    str_taille[0] = '%';
    strcpy(&str_taille[1], longueurStr);
    if (status == 0 || status == 1) status_bis = 1;
    else status_bis = status;
    
    for (i =0;i<10+status_bis;i++){
        str_taille[i+2] = lettre_acceptee[i];
    }
    str_taille[10 + status_bis+1] = ']';
    str_taille[10 + status_bis+2] = '\0';
    //printf("str_taille: %s , Taille : %d\n", str_taille, strlen(str_taille));

    //###########################################################################

    phrase_mod[0] = "La lettre";
    phrase_mod[1] = "L etat";
    phrase_mod[2] = "La regle";

    tryagain:      //Reprise du code apres erreur de saisie
    val1 = 0;      //Variable servant à la décision d'un choix
    essai++;       //Incrémentation de l'essai


    printf("Essai n°%d | Entrer %s n°%d \n",essai,phrase_mod[status] ,index);

    scanf(str_taille, chaine_verif);                //Saisie du clavier
    //printf("chaine_verif: %s\n", chaine_verif);
    size_t len_saisie = strlen(chaine_verif);       //Longueur de la saisie clavier

    int occ =0;
    while ((c = fgetc(stdin)) != '\n' && c != EOF){ // CHECK si l'entree est trop longue
        occ ++;
    }
    
    if (occ != 0 || len_saisie ==0){
        printf("Saisie de mauvaise longueur \n");   //Mauvaise Longueur
        goto tryagain;
    }

    if (status == 0 || status == 1){
        for (int w = 0 ; w<longueur;w++){    //Init saisie = {"0000..."}
            saisie[w] = '0';
        }
        saisie[longueur] = '\0';
    }
    for (size_t k = 0; k<len_saisie;k++){
            saisie[k] = chaine_verif[k]; // Copie de la saisie dans la variable de controle
    }
    //___________________________________________________________________________________//
    int choix1;
    if (status == 0 || status == 1){
        if (len_saisie != (size_t)longueur ){
            while(val1 != 2){
                printf("Etes vous sur d enregistrer %s comme %s ?\n", saisie,phrase_mod[status]);
                printf("\nOUI : 0 / NON : 1\n");
                scanf("%d", &choix1);
                switch(choix1){
                    case 0:
                        val1 = 2;
                        getchar();
                        break;
                    case 1:
                        val1 = 2;
                        getchar();
                        goto tryagain;
                }
            }
        }
        alphabet_verif[index] = saisie;
        for (int j = 0; j<index;j++){       //VERIF REDONDANCE
            if (strcmp(saisie,alphabet_verif[j]) == 0)
            {
                printf("%s %s est deja saisi(e) index: %d\n",phrase_mod[status], saisie,j);
                goto tryagain;
            }
            //printf("alphabet_verif depuis lib : %s\n", alphabet_verif[j]);
        }
    }

    else if (status == 2) {
        regles_verif[index] = saisie;
        if (saisie[nb_octets] != '-' || saisie[2*nb_octets+1] != '-' || len_saisie != (size_t)longueur)
        {
            printf("Saisie de mauvaise longueur ou erronee \n");
            goto tryagain;
        }
        saisie[longueur] = '\0';
        for (int j = 0; j<index;j++){       //VERIF REDONDANCE
            if (strcmp(saisie,regles_verif[j]) == 0)
            {
                printf("%s %s est deja saisi(e): \n",phrase_mod[status], saisie);
                goto tryagain;
            }
        }
    }
    printf("SAISIE: %s\n", saisie);
    free(chaine_verif);
    return saisie;
}

char **read_input_etats(int longueur, int mode, int nb_etats_a_saisir, char **liste_a_comparer, int len_liste_a_comparer)
{

    char **etats_verif;
    etats_verif = malloc(nb_etats_a_saisir * sizeof(malloc(longueur * sizeof(char))));
    //alphabet_verif = realloc(alphabet_verif, (len_liste_a_comparer +nb_etats_a_saisir) * sizeof(malloc(nb_octets * sizeof(char))));
    //alphabet_verif = malloc((len_liste_a_comparer +nb_etats_a_saisir) * sizeof(malloc(nb_octets * sizeof(char))));
    /*
    for(int i=0; i<mode ; i++){
        printf("alphabet_verif depuis librairies : %s\n", alphabet_verif[i]);
    }*/

    //NUMERO 2.2
    //etats_verif = realloc(etats_verif,nb * sizeof(malloc(nb_octets * sizeof(char))));
    int essai = 0;
    int index;
    


    //VERIF DE LA REDONDANCE DE SAISIE DES ETATS PAR RAPPORT AUX LETTRES
    //VERIF DE L'INCLUSION DES ETATS INITIAUX ET FINAUX DANS ETATS

    for (int i = 0; i < nb_etats_a_saisir; i++)
    {
        essai = 0;
        if (mode == 0 || mode == 1) index = i;
        else index = mode;

        etats_verif[i] = read_input_letter(longueur, index, 1);
        etats_verif[i][longueur] = '\0';
        for (int j = 0; j < len_liste_a_comparer; j++)
        {
            if (strcmp(etats_verif[i], liste_a_comparer[j]) == 0)
            {
                if (mode == 0)
                {
                    printf("Cette saisie est enregistree en tant que lettre de l alphabet \n");
                    i--;
                }
                else
                    essai++;
                break;
            }
        }
        if (mode == 1 && essai == 0)
        {
            printf("Cette saisie n'est pas ete enregistree en tant qu etat au prealable \n");
            i--;
        }
        if (mode != 0 && mode != 1) mode ++;
    }


    return etats_verif;
}

int verif_syntax(char *regle_a_verif, char **liste_a_comparer, int nb_debut, int nb_fin)
{
    int val_verif_syntax = 0;

    for (int i = nb_debut; i < nb_fin; i++)
    {
        if (!strcmp(regle_a_verif, liste_a_comparer[i])){
            val_verif_syntax = 1;
            break;
        }
    }
    return val_verif_syntax;
}

char **read_input_regle(int longueur, char **liste_a_comparer, int nb1, int nb2, int index)
{
    int i, verite;
    
    char *saisie_v2 = malloc(3 * longueur * sizeof(char) + 2); //Allocation memoire de la saisie
    //Allocation memoire de regles_normal
    char **regles_normal;
    regles_normal = malloc(3 * sizeof(char*));
    for (i = 0; i<3; i++){
      regles_normal[i] = malloc(longueur * sizeof(char));
    }

    //Allocation memoire des caracteres de la saisie
    char *etat1 = malloc(longueur * sizeof(char));
    char *etat2 = malloc(longueur * sizeof(char));
    char *lettre = malloc(longueur * sizeof(char));
    /*
    for (int i = 0; i<nb1+nb2;i++){
        printf("Caracteres a comparer a comparer: %s\n", liste_a_comparer[i]);
    }*/

    do {
        verite = 1;
        saisie_v2 = read_input_letter(2 + 3 * longueur, index, 2); //Saisie regle du type "1-a-2"
        for (int i = 0; i < 2 + 3 * longueur; i++)
        {
            //printf("caractere %d : %c\n", i, saisie_v2[i]);
            
            if (i < longueur) etat1[i] = saisie_v2[i]; //Saisie[0:nb_octets] -> Etat 1

            else if (longueur < i && i < 2 * longueur + 1) lettre[i - longueur - 1] = saisie_v2[i]; //Saisie[nb_octets+1:2*nb_octets+1] -> Lettre

            else if (2 * longueur + 1 < i) etat2[i - 2 * longueur - 2] = saisie_v2[i]; //Saisie[2*nb_octets+2:3*nb_octets+2] -> Etat 2

        }

        etat1[longueur] = '\0';
        lettre[longueur] = '\0';
        etat2[longueur] = '\0';


        for (int i = 0; i<nb1+nb2;i++){
            liste_a_comparer[i][nb_octets] = '\0';
        }
        
        verite += verif_syntax(etat1,liste_a_comparer,nb2, nb2 + nb1); //Ca merde
        
        verite += verif_syntax(etat2, liste_a_comparer, nb2, nb2 + nb1);
        
        verite += verif_syntax(lettre, liste_a_comparer,0,nb2);
        
        if (verite <4) printf("Saisie de l'etat ou de la lettre n'existant pas\n");
    
    } while (verite !=4);


    for(int i = 0;i<longueur;i++) {regles_normal[0][i]=etat1[i];}
    for(int i = 0;i<longueur;i++) {regles_normal[1][i]=lettre[i];}
    for(int i = 0;i<longueur;i++) {regles_normal[2][i]=etat2[i];}
    regles_normal[0][longueur] = '\0';
    regles_normal[1][longueur] = '\0';
    regles_normal[2][longueur] = '\0';


    return regles_normal;

}

int verif_element_in_tab_3D(char ***tab, int len_tab, char **element){
    int i;
    for (i =0; i<len_tab; i++){
        if (strcmp(tab[i][0], element[0]) == 0) {
            return 0;
            break;
        }
    }
    return 1;
}

int verif_element_in_tab_2D(char **tab, int len_tab, char *element){
    int i;
    for (i =0; i<len_tab; i++){
        if (strcmp(tab[i],element)==0) {
            return 0;
            break;
        }
    }
    return 1;
}

void affiche_alphabet(AEF* aef){
    printf("\nAlphabet: ");
    for (int i = 0; i<aef->nb_letters; i++){
        printf(" %s ", aef->alphabet[i]);
    }
    printf("\n");
}

void affiche_etats(AEF* aef){
    int i;
    printf("\nEtat(s): ");
    for (i = 0; i<aef->nb_etats; i++){
        printf(" %s ", aef->etats[0][i]);
    }
    printf("\nEtat(s) initial(aux): ");
    for (i = 0; i<aef->nb_etats_init; i++){
        printf(" %s ", aef->etats[1][i]);
    }
    printf("\nEtat(s) final(aux): ");
    for (i = 0; i<aef->nb_etats_end; i++){
        printf(" %s ", aef->etats[2][i]);
    }
    printf("\n");
}

void affiche_liste_compare(AEF* aef){
    int i;
    printf("\nListe a comparer (alphabet + etats):\n");
    for (i = 0; i<aef->nb_letters+aef->nb_etats; i++){
        printf("%s", aef->liste_a_comparer[i]);
    }
    printf("\n");
}

void affiche_regles(AEF* aef){
    printf("\nRegles: ");
    for (int i = 0; i<aef->nb_regles; i++){
        printf("\n     %s -> %s -> %s ", aef->regles[i][0],aef->regles[i][1],aef->regles[i][2]);
    }
    printf("\n");
}

void affiche_dict(ht* table){
    hti it = ht_iterator(table);
    printf("\nDictionnaire fini\n");
    while (ht_next(&it)) {
        printf("Key: %s {\n", it.key);
        for(int i = 0; i < it.nb_rules_by_etat; i++){
            printf("       {%s->%s}\n", it.tableau_etats[i][0],it.tableau_etats[i][1]);
        }
        printf("            }\n");
    }
    printf("\n");
}

void affiche_AEF(AEF* aef){
    affiche_alphabet(aef);
    affiche_etats(aef);
    affiche_regles(aef);
    affiche_dict(aef->dict_table);
}

int sup_check_regle(char *lettre, AEF* aef, int mode){
    int i, val,tmp1,tmp2;
    if (mode == 0){
        tmp1 = 1;
        tmp2 = 1;
    }
    else if(mode == 1){
        tmp1 = 0;
        tmp2 = 2;
    }
    for(i=0; i<aef->nb_regles;i++){
        if(strcmp(lettre, aef->regles[i][tmp1])== 0 || strcmp(lettre, aef->regles[i][tmp2])==0){
            do{
                printf("Voulez vous supprimer la lettre %s sachant qu'elle\n", lettre);
                printf("impliquera une suppression des regles ou elle est inclue\n");
                printf("\nOUI : 1 / NON : 2\n");
                scanf("%d", &val);
                switch (val) {
                    case 1:
                        return 0;
                        break;
                    case 2:
                        return 1;
                        break;
                    default:
                        printf("\n#--------Attention choisissez entre 1 et 2-------#\n");
                }
            }while(val < 0 || val > 2);
        }
        
    }
    return 2;
}

void sup_let_in_alpha(char *lettre, AEF* aef){
    int i,index;
    for(i=0; i<aef->nb_letters;i++){
        if(strcmp(lettre, aef->alphabet[i])==0){
            for (index = i ; index < aef->nb_letters-1 ; index++){
                aef->alphabet[index] = aef->alphabet[index+1];
            }
            aef->nb_letters --;
            i--;
        }
    }
}

void sup_etat_in_etats(char *etat, AEF* aef){
    int i,index;
    for(i=0; i<aef->nb_etats;i++){
        if(strcmp(etat, aef->etats[0][i])==0){
            for (index = i ; index < aef->nb_etats-1 ; index++){
                aef->etats[0][index] = aef->etats[0][index+1];
            }
            aef->nb_etats --;
            i--;
        }
    }
}

void sup_etat_in_etats_initiaux(char *etat, AEF* aef){
    int i,index;
    for(i=0; i<aef->nb_etats_init;i++){
        if(strcmp(etat, aef->etats[1][i])==0){
            for (index = i ; index < aef->nb_etats_init-1 ; index++){
                aef->etats[1][index] = aef->etats[1][index+1];
            }
            aef->nb_etats_init --;
            i--;
        }
    }
}

void sup_etat_in_etats_finaux(char *etat, AEF* aef){
    int i,index;
    for(i=0; i<aef->nb_etats_end;i++){
        if(strcmp(etat, aef->etats[2][i])==0){
            for (index = i ; index < aef->nb_etats_end-1 ; index++){
                aef->etats[2][index] = aef->etats[2][index+1];
            }
            aef->nb_etats_end --;
            i--;
        }
    }
}

void sup_regle_by_lettre(char *lettre, AEF* aef, int mode){
    int i,index;
    for(i=0; i<aef->nb_regles;i++){
        if (mode ==0){
            if(strcmp(lettre, aef->regles[i][1])==0){
                for (index = i ; index < aef->nb_regles-1; index++){
                    aef->regles[index] = aef->regles[index+1];
                }
                affiche_regles(aef);
                aef->nb_regles --;
                i--;
            }
        }
        else if(mode ==1){
            if(strcmp(lettre, aef->regles[i][0])==0 || strcmp(lettre, aef->regles[i][2])==0){
                for (index = i ; index < aef->nb_regles-1; index++){
                    aef->regles[index] = aef->regles[index+1];
                }
                affiche_regles(aef);
                aef->nb_regles --;
                i--;
            }
        }
    }
}

void sup_regle_by_regle(char **regle, AEF* aef){
    int i,index;
    for(i=0; i<aef->nb_regles;i++){
        if(strcmp(regle[0], aef->regles[i][0])==0 && strcmp(regle[1], aef->regles[i][1])==0 && strcmp(regle[2], aef->regles[i][2])==0){
            for (index = i ; index < aef->nb_regles-1; index++){
                aef->regles[index] = aef->regles[index+1];
            }
            affiche_regles(aef);
            aef->nb_regles --;
            i--;
        }
    }
}
