#include "../headers/functions/ht.h"
typedef struct AEF AEF;

struct AEF{
  char **alphabet;
  char **liste_a_comparer;
  char ***etats;
  char ***regles;
  int nb_letters, nb_etats,nb_etats_init, nb_etats_end,nb_regles;
  ht* dict_table;
};

void start_2();
AEF input_AEF(AEF aef);
