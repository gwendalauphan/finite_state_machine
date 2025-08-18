typedef struct Alpha_Mot Alpha_Mot;

struct Alpha_Mot{
  char **alphabet;
  char *mot;
  char **liste_a_comparer;
  int nb_letters_alpha,nb_letters_mot;
};

void start_1();
Alpha_Mot input_Alpha_Mot(Alpha_Mot alpha_mot);
