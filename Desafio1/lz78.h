#ifndef LZ78_H
#define LZ78_H
#include "lectura.h"

void copiar(char *dest, char *src);
char* concat_strings(const char* prefix, char c);
int search_dict(char **dict, int dict_len, char *input, int start, int inlen, int *match_len);
int string_length(const char* s);

int longitud(char *s);
void lz78_compress(char *input, int **out_prefix, char **out_char, int *out_size);
unsigned char* lz78_decompress(const unsigned char* compressed_data, unsigned int data_size);
int longitudE(unsigned char *s);
#endif // LZ78_H
