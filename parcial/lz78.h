#ifndef LZ78_H
#define LZ78_H
#include "lectura.h"

void copiar(char *dest, char *src);
char *concat_dict(char **dict, int idx, char c);
int search_dict(char **dict, int dict_len, char *input, int start, int inlen, int *match_len);
int longitud(char *s);
void lz78_compress(char *input, int **out_prefix, char **out_char, int *out_size);
void lz78_decompress(int *prefix, char *ch, int n);
#endif // LZ78_H
