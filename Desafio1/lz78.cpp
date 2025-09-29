
#include "lz78.h"
/*
bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

int string_length(const char* s) {
    if (!s) return 0;
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

char* concat_strings(const char* prefix, char c) {
    int prefix_len = string_length(prefix);
    char* new_str = new char[prefix_len + 2];

    for (int i = 0; i < prefix_len; ++i) {
        new_str[i] = prefix[i];
    }

    new_str[prefix_len] = c;
    new_str[prefix_len + 1] = '\0';
    return new_str;
}

unsigned char* lz78_decompress(const unsigned char* compressed_data, unsigned int data_size) {
    long long result_capacity = data_size * 2;
    if (result_capacity < 256) result_capacity = 256;
    unsigned char* result = new unsigned char[result_capacity];
    long long result_size = 0;
    char** dictionary = new char*[data_size];
    int dict_len = 0;
    long long cursor = 0;
    while (cursor < data_size) {
    }
        int prefix_index = 0;
        while (cursor < data_size && is_digit(compressed_data[cursor])) {
            prefix_index = prefix_index * 10 + (compressed_data[cursor] - '0');
            cursor++;
        }

        if (cursor >= data_size) {

            break;
        }
        char current_char = compressed_data[cursor];
        cursor++;

        char* new_entry = nullptr;
        if (prefix_index == 0) {
            new_entry = concat_strings(nullptr, current_char);
        } else {
            if (prefix_index - 1 < dict_len) {
                new_entry = concat_strings(dictionary[prefix_index - 1], current_char);
            } else {
                std::cerr << "Error: Indice de prefijo invalido." << std::endl;
                break;
            }
        }

        int entry_len = string_length(new_entry);
        if (result_size + entry_len + 1 > result_capacity) {
            result_capacity *= 2;
            unsigned char* new_result = new unsigned char[result_capacity];
            for (long long i = 0; i < result_size; ++i) {
                new_result[i] = result[i];
            }
            delete[] result;
            result = new_result;
        }
        for (int i = 0; i < entry_len; ++i) {
            result[result_size + i] = new_entry[i];
        }
        result_size += entry_len;

        dictionary[dict_len] = new_entry;
        dict_len++;
    }

    result[result_size] = '\0';

    for (int i = 0; i < dict_len; ++i) {
        delete[] dictionary[i];
    }
    delete[] dictionary;

    return result;
}
*/

int longitudE(unsigned char *s) {
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

