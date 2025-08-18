#include <stdio.h>
#include <stdlib.h>
#ifndef RESSOURCES_H
#define RESSOURCES_H
#endif

#ifdef VAR_GLOBALES
    int nb_octets =1, len_mot = 100; 
    //int nb_letters = 5, nb_rules = 2;
    char **alphabet_verif, etats_verif, regles_normal;
    char** regles_verif;
#else
    extern int nb_octets,len_mot;
    //extern int nb_letters, nb_rules;
    extern char **alphabet_verif,etats_verif,regles_normal;
    extern char **regles_verif;
#endif



/*
#ifdef VAR_GLOBALES
    int nb_octets =1, len_mot = 100; 
    int nb_letters_verif, nb_rules_verif;
    char **alphabet_verif;  //redondance saisie (lettre + etat)
    char **etats_verif;     //return de read_input_etats
    char ** regles_verif;   //redondance saisie regles
    char ** regles_normal;  //return de read_input_regle
#else
    extern int nb_octets,len_mot;
    extern int nb_letters_verif, nb_rules_verif;
    extern char **alphabet_verif;
    extern char **etats_verif;
    extern char **regles_verif;
    extern char **regles_normal;
#endif
#endif



*/
