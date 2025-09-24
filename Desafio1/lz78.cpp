#include "lz78.h"

void copiar(char *dest, char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
char *concat_dict(char **dict, int idx, char c){
    int len = 0;
    if (idx >= 0) len = longitud(dict[idx]);
    char *newstr = (char*)malloc(len + 2);
    int i;
    for (i = 0; i < len; i++) {
        newstr[i] = dict[idx][i];
    }
    newstr[i++] = c;
    newstr[i] = '\0';
    return newstr;
}
int search_dict(char **dict, int dict_len, char *input, int start, int inlen, int *match_len){
    int max_idx = -1, max_len = 0;
    for (int i = 0; i < dict_len; i++) {
        int len = longitud(dict[i]);
        if (len == 0) continue;
        if (start + len > inlen) continue;
        int found = 1;
        for (int j = 0; j < len; j++) {
            if (dict[i][j] != input[start + j]) {
                found = 0;
                break;
            }
        }
        if (found && len > max_len) {
            max_len = len;
            max_idx = i;
        }
    }
    *match_len = max_len;
    return max_idx;
}
int longitud(char *s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

int longitudE(unsigned char *s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

void lz78_compress(char *input, int **out_prefix, char **out_char, int *out_size){
    int inlen = longitud(input);
    char **dict = (char**)malloc(sizeof(char*) * (inlen+1));
    int dict_len = 0;
    int MAX_WORD_SIZE = inlen + 1;
    for (int i = 0; i < inlen+1; i++) {
        dict[i] = (char*)malloc(MAX_WORD_SIZE);
        dict[i][0] = '\0';
    }
    int *prefix = (int*)malloc(sizeof(int) * inlen);
    char *ch = (char*)malloc(sizeof(char) * inlen);
    int outlen = 0;
    int i = 0;
    while (i < inlen) {
        int match_len = 0;
        int idx = search_dict(dict, dict_len, input, i, inlen, &match_len);
        if (idx == -1) {
            prefix[outlen] = 0;
            ch[outlen] = input[i];
            dict[dict_len][0] = input[i];
            dict[dict_len][1] = '\0';
            dict_len++;
            i++;
        } else {
            if (i + match_len < inlen) {
                prefix[outlen] = idx + 1;
                ch[outlen] = input[i + match_len];
                char *newstr = concat_dict(dict, idx, input[i + match_len]);
                copiar(dict[dict_len], newstr);
                free(newstr);
                dict_len++;
                i += match_len + 1;
            } else {
                break;
            }
        }
        outlen++;
    }
    *out_prefix = (int*)malloc(sizeof(int) * outlen);
    *out_char = (char*)malloc(sizeof(char) * outlen);
    for (int j = 0; j < outlen; j++) {
        (*out_prefix)[j] = prefix[j];
        (*out_char)[j] = ch[j];
    }
    *out_size = outlen;
    for (int j = 0; j < inlen+1; j++) free(dict[j]);
    free(dict);
    free(prefix);
    free(ch);
}
void lz78_decompress(int *prefix, char *ch, int n) {
    char **dict = (char**)malloc(sizeof(char*) * (n+1));
    int MAX_WORD_SIZE = longitud(ch);
    for (int i = 0; i < n+1; i++) {
        dict[i] = (char*)malloc(MAX_WORD_SIZE);
        dict[i][0] = '\0';
    }
    ofstream fout("salida.txt", std::ios::out | std::ios::binary);
    if (!fout) {
        cout << "No se pudo abrir salida.txt\n";
        return;
    }
    int dict_len = 0;
    for (int i = 0; i < n; i++) {
        int p = prefix[i];
        char c = ch[i];
        if (p == 0) {
            dict[dict_len][0] = c;
            dict[dict_len][1] = '\0';
        } else {
            int j = 0;
            while (dict[p-1][j] != '\0') {
                dict[dict_len][j] = dict[p-1][j];
                j++;
            }
            dict[dict_len][j] = c;
            dict[dict_len][j+1] = '\0';
        }
        // Escribir dict[dict_len] en archivo
        int j = 0;
        while (dict[dict_len][j] != '\0') {
            fout.put(dict[dict_len][j]);
            j++;
        }
        dict_len++;
    }
    fout.close();
    for (int i = 0; i < n+1; i++) free(dict[i]);
    free(dict);
}
