#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../headers/functions/utils_split.h"
#include "../../headers/ressources.h"
#include "../../headers/part_2.h"
#include "../../headers/functions/demo.h"

#define INPUT_PATH "data/fileToRead.txt"

static void free_rules(char ***regles, int nb_regles) {
    if (!regles) return;
    for (int i = 0; i < nb_regles; ++i) {
        if (regles[i]) {
            // 3 tokens per règle (assuming), but if variable, track sizes separately
            for (int j = 0; j < 3; ++j) free(regles[i][j]);
            free(regles[i]);
        }
    }
    free(regles);
}

static void free_aef_partial(AEF *aef) {
    if (!aef) return;
    if (aef->alphabet)      free_tokens(aef->alphabet, aef->nb_letters);
    if (aef->etats) {
        if (aef->etats[0])  free_tokens(aef->etats[0], aef->nb_etats);
        if (aef->etats[1])  free_tokens(aef->etats[1], aef->nb_etats_init);
        if (aef->etats[2])  free_tokens(aef->etats[2], aef->nb_etats_end);
        free(aef->etats);
    }
    if (aef->regles)        free_rules(aef->regles, aef->nb_regles);
    if (aef->liste_a_comparer) free(aef->liste_a_comparer);
    // aef->dict_table: free it if dictionnary() allocates something (not shown here)
    memset(aef, 0, sizeof(*aef));
}

AEF read_file(AEF aef) {
    memset(&aef, 0, sizeof(aef));  // start clean

    FILE *file = fopen(INPUT_PATH, "r");
    if (!file) {
        perror("fopen");
        return aef;
    }

    aef.etats = (char***)calloc(3, sizeof(char**)); // 3 groups: all states, initial, final
    if (!aef.etats) { fclose(file); return aef; }

    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int lineCount = -1;

    while ((read = getline(&line, &len, file)) != -1) {
        lineCount++;

        // Split on space: we expect something like "key value"
        int parts = 0;
        char **result = split_exact(' ', line, &parts, 0);
        if (!result || parts < 2) {
            fprintf(stderr, "Invalid line %d: expected at least 2 space-separated fields\n", lineCount+1);
            free_tokens(result, parts);
            free(line);
            fclose(file);
            free_aef_partial(&aef);
            return aef;
        }

        // result[1] holds the payload part (as in your code)
        switch (lineCount) {
            case 0: { // size (octets)
                char *endp = NULL;
                long v = strtol(result[1], &endp, 10);
                if (endp == result[1] || v <= 0) {
                    fprintf(stderr, "Invalid octet size on line 1\n");
                    free_tokens(result, parts);
                    free(line);
                    fclose(file);
                    free_aef_partial(&aef);
                    return aef;
                }
                int SizeOctet = (int)v;
                nb_octets = SizeOctet;
                printf("Octet size: %d\n", SizeOctet);
            } break;

            case 1: { // alphabet "a-b-c"
                int n = 0;
                aef.alphabet = split_exact('-', result[1], &n, (size_t)nb_octets);
                if (!aef.alphabet) {
                    fprintf(stderr, "Invalid alphabet on line 2\n");
                    free_tokens(result, parts);
                    free(line);
                    fclose(file);
                    free_aef_partial(&aef);
                    return aef;
                }
                aef.nb_letters = n;
                printf("Alphabet:\n");
                for (int i = 0; i < aef.nb_letters; ++i) printf("%s\n", aef.alphabet[i]);
            } break;

            case 2: { // rules "q0,a,q1-q1,b,q2-..."
                int bigParts = 0;
                char **tmp = split_exact('-', result[1], &bigParts, (size_t)(nb_octets*3 + 2));
                if (!tmp) {
                    fprintf(stderr, "Invalid rules block on line 3\n");
                    free_tokens(result, parts);
                    free(line);
                    fclose(file);
                    free_aef_partial(&aef);
                    return aef;
                }

                aef.nb_regles = bigParts;
                aef.regles = (char***)calloc((size_t)aef.nb_regles, sizeof(char**));
                if (!aef.regles) {
                    free_tokens(tmp, bigParts);
                    free_tokens(result, parts);
                    free(line);
                    fclose(file);
                    free_aef_partial(&aef);
                    return aef;
                }

                for (int i = 0; i < aef.nb_regles; ++i) {
                    int t = 0;
                    // each rule: "src,sym,dst" — enforce nb_octets per field
                    aef.regles[i] = split_exact(',', tmp[i], &t, (size_t)nb_octets);
                    if (!aef.regles[i] || t != 3) {
                        fprintf(stderr, "Invalid rule %d on line 3\n", i+1);
                        free_tokens(tmp, bigParts);
                        free_tokens(result, parts);
                        free(line);
                        fclose(file);
                        free_aef_partial(&aef);
                        return aef;
                    }
                }

                printf("Regles:\n");
                for (int i = 0; i < aef.nb_regles; ++i) {
                    printf("%s %s %s\n", aef.regles[i][0], aef.regles[i][1], aef.regles[i][2]);
                }

                free_tokens(tmp, bigParts); // tmp was only an intermediate container
            } break;

            case 3: { // states
                int n = 0;
                aef.etats[0] = split_exact('-', result[1], &n, (size_t)nb_octets);
                if (!aef.etats[0]) {
                    fprintf(stderr, "Invalid states on line 4\n");
                    free_tokens(result, parts);
                    free(line);
                    fclose(file);
                    free_aef_partial(&aef);
                    return aef;
                }
                aef.nb_etats = n;
                printf("Etats:\n");
                for (int i = 0; i < aef.nb_etats; ++i) printf("%s\n", aef.etats[0][i]);
            } break;

            case 4: { // initial states
                int n = 0;
                aef.etats[1] = split_exact('-', result[1], &n, (size_t)nb_octets);
                if (!aef.etats[1]) {
                    fprintf(stderr, "Invalid initial states on line 5\n");
                    free_tokens(result, parts);
                    free(line);
                    fclose(file);
                    free_aef_partial(&aef);
                    return aef;
                }
                aef.nb_etats_init = n;
                printf("Etats Initiaux:\n");
                for (int i = 0; i < aef.nb_etats_init; ++i) printf("%s\n", aef.etats[1][i]);
            } break;

            case 5: { // final states
                int n = 0;
                aef.etats[2] = split_exact('-', result[1], &n, (size_t)nb_octets);
                if (!aef.etats[2]) {
                    fprintf(stderr, "Invalid final states on line 6\n");
                    free_tokens(result, parts);
                    free(line);
                    fclose(file);
                    free_aef_partial(&aef);
                    return aef;
                }
                aef.nb_etats_end = n;
                printf("Etats Finaux:\n");
                for (int i = 0; i < aef.nb_etats_end; ++i) printf("%s\n", aef.etats[2][i]);
            } break;

            default:
                fprintf(stderr, "Unexpected extra content on line %d\n", lineCount+1);
                // You can decide to treat this as error or ignore.
                break;
        }

        // this `result` only belongs to this iteration
        free_tokens(result, parts);
    }

    // Build liste_a_comparer (just pointers; do NOT free underlying strings)
    {
        int total = aef.nb_letters + aef.nb_etats;
        aef.liste_a_comparer = (char**)malloc((size_t)total * sizeof(char*));
        if (!aef.liste_a_comparer) {
            free(line);
            fclose(file);
            free_aef_partial(&aef);
            return aef;
        }
        for (int i = 0; i < total; ++i) {
            if (i < aef.nb_letters) aef.liste_a_comparer[i] = aef.alphabet[i];
            else                    aef.liste_a_comparer[i] = aef.etats[0][i - aef.nb_letters];
        }
    }

    aef.dict_table = dictionnary(aef); // make sure to free it somewhere in your code

    free(line);
    fclose(file);
    return aef;
}
