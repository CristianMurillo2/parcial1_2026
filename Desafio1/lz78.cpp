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

// --- Funciones auxiliares para no usar <cstring> ---

// Implementación simple de strlen
size_t strlen_manual(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Implementación simple de strcpy
void strcpy_manual(char* dest, const char* src) {
    size_t i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

/**
 * @brief Descomprime datos LZ78 sin usar librerías STL.
 * @param prefix Puntero al array de índices del diccionario (1-based).
 * @param ch Puntero al array de caracteres.
 * @param n El número de pares (prefijo, caracter).
 * @param decompressed_size Referencia donde se almacenará el tamaño final.
 * @return Un puntero a un nuevo buffer (unsigned char*) con los datos descomprimidos.
 * ¡IMPORTANTE! El código que llama a esta función es responsable de liberar esta memoria usando delete[].
 */
unsigned char* lz78_decompress_no_lib(const int* prefix, const unsigned char* ch, int n, size_t& decompressed_size) {
    // 1. --- Configuración del diccionario (array de punteros a char) ---
    if (n <= 0) {
        decompressed_size = 0;
        return nullptr;
    }
    char** dictionary = new char*[n];
    size_t dictionary_len = 0;

    // 2. --- Configuración del buffer de salida dinámico ---
    size_t output_capacity = 256; // Capacidad inicial
    size_t output_size = 0;
    unsigned char* output_buffer = new unsigned char[output_capacity];

    // 3. --- Bucle principal de descompresión ---
    for (int i = 0; i < n; ++i) {
        int prefix_index = prefix[i];
        char current_char = static_cast<char>(ch[i]);
        char* new_word = nullptr;
        size_t new_word_len = 0;

        if (prefix_index == 0) {
            // Caso base: el caracter es nuevo.
            new_word_len = 1;
            new_word = new char[2]; // 1 para el char + 1 para el '\0'
            new_word[0] = current_char;
            new_word[1] = '\0';
        } else {
            // El nuevo término es una entrada existente + el nuevo caracter.
            size_t dict_idx = static_cast<size_t>(prefix_index - 1);
            if (dict_idx >= dictionary_len) {
                std::cerr << "Error: Índice de prefijo inválido: " << prefix_index << std::endl;
                // Liberar toda la memoria asignada antes de salir
                delete[] output_buffer;
                for (size_t k = 0; k < dictionary_len; ++k) delete[] dictionary[k];
                delete[] dictionary;
                decompressed_size = 0;
                return nullptr;
            }

            const char* prefix_word = dictionary[dict_idx];
            size_t prefix_len = strlen_manual(prefix_word);
            new_word_len = prefix_len + 1;
            new_word = new char[new_word_len + 1]; // +1 para el '\0'

            strcpy_manual(new_word, prefix_word);
            new_word[prefix_len] = current_char;
            new_word[new_word_len] = '\0';
        }

        // Añadir la nueva palabra al buffer de salida, redimensionando si es necesario.
        if (output_size + new_word_len > output_capacity) {
            size_t new_capacity = output_capacity * 2;
            if (new_capacity < output_size + new_word_len) {
                new_capacity = output_size + new_word_len;
            }
            unsigned char* new_buffer = new unsigned char[new_capacity];
            for (size_t j = 0; j < output_size; ++j) {
                new_buffer[j] = output_buffer[j];
            }
            delete[] output_buffer;
            output_buffer = new_buffer;
            output_capacity = new_capacity;
        }

        // Copiar la nueva palabra al buffer de salida
        for (size_t j = 0; j < new_word_len; ++j) {
            output_buffer[output_size++] = static_cast<unsigned char>(new_word[j]);
        }

        // Añadir la nueva palabra al diccionario.
        dictionary[dictionary_len++] = new_word;
    }

    // 4. --- Limpieza y preparación del resultado final ---
    decompressed_size = output_size;
    unsigned char* final_result = new unsigned char[decompressed_size];
    for (size_t i = 0; i < decompressed_size; ++i) {
        final_result[i] = output_buffer[i];
    }

    // Liberar toda la memoria intermedia
    delete[] output_buffer;
    for (size_t i = 0; i < dictionary_len; ++i) {
        delete[] dictionary[i];
    }
    delete[] dictionary;

    return final_result;
}
