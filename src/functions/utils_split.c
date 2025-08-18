// utils_split.c
#include <stdlib.h>
#include <string.h>
#include "../../headers/functions/utils_split.h"

static int count_tokens(const char *s, char d) {
    int n = 1;
    for (const char *p = s; *p && *p != '\n'; ++p) {
        if (*p == d) ++n;
    }
    return n;
}

char **split_exact(char delimiter, const char *string, int *out_size, size_t max_token_len) {
    if (!string || !out_size) return NULL;

    // Only consider up to '\n'
    const char *end = strchr(string, '\n');
    size_t len = end ? (size_t)(end - string) : strlen(string);

    int count = count_tokens(string, delimiter);
    char **out = (char**)calloc((size_t)count, sizeof(char*));
    if (!out) return NULL;

    int idx = 0;
    const char *start = string;
    const char *cur = string;
    while ((size_t)(cur - string) < len) {
        if (*cur == delimiter) {
            size_t tlen = (size_t)(cur - start);
            if (max_token_len > 0 && tlen > max_token_len) { // invalid: too long
                for (int i = 0; i < idx; ++i) free(out[i]);
                free(out);
                return NULL;
            }
            out[idx] = (char*)malloc(tlen + 1);
            if (!out[idx]) {
                for (int i = 0; i < idx; ++i) free(out[i]);
                free(out);
                return NULL;
            }
            memcpy(out[idx], start, tlen);
            out[idx][tlen] = '\0';
            idx++;
            start = cur + 1;
        }
        cur++;
    }
    // last token
    size_t tlen = (size_t)(cur - start);
    if (max_token_len > 0 && tlen > max_token_len) {
        for (int i = 0; i < idx; ++i) free(out[i]);
        free(out);
        return NULL;
    }
    out[idx] = (char*)malloc(tlen + 1);
    if (!out[idx]) {
        for (int i = 0; i < idx; ++i) free(out[i]);
        free(out);
        return NULL;
    }
    memcpy(out[idx], start, tlen);
    out[idx][tlen] = '\0';
    idx++;

    *out_size = idx;
    return out;
}

void free_tokens(char **tokens, int count) {
    if (!tokens) return;
    for (int i = 0; i < count; ++i) free(tokens[i]);
    free(tokens);
}
