// utils_split.h
#pragma once
#include <stddef.h>

/* Split `string` on `delimiter` (stopping at '\n' if present).
 * - Allocates exact-length, NUL-terminated tokens.
 * - If max_token_len > 0, enforces max length (excluding NUL).
 * Returns: array of char* in *out_size, or NULL on error.
 */
char **split_exact(char delimiter, const char *string, int *out_size, size_t max_token_len);

/* Free an array returned by split_exact */
void free_tokens(char **tokens, int count);