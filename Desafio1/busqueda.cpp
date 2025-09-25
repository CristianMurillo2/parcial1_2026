#include "busqueda.h"
#include <iostream>
using namespace std;

int encontrarPista(const unsigned char* textoOriginal, const char* textoPista) {
    int lenPista = 0;
    while (textoPista[lenPista] != '\0') {
        lenPista++;
    }

    if (lenPista == 0) {
        return 1;
    }

    int lenOriginal = 0;
    while (textoOriginal[lenOriginal] != '\0') {
        lenOriginal++;
    }

    if (lenPista > lenOriginal) {
        return 0;
    }

    for (int i = 0; i <= lenOriginal - lenPista; ++i) {

        bool esCoincidencia = true;
        int izquierda = 0;
        int derecha = lenPista - 1;

        if (textoOriginal[i + derecha] != textoPista[derecha]) {
            continue;
        }

        while (izquierda <= derecha) {
            esCoincidencia = true;
            if (textoOriginal[i + derecha] != textoPista[derecha]) {
                esCoincidencia = false;
                break;
            }

            if (textoOriginal[i + izquierda] != textoPista[izquierda]) {
                esCoincidencia = false;
                break;
            }

            izquierda++;
            derecha--;
        }

        if (esCoincidencia) {
            return 1;
        }
    }

    return 0;
}

