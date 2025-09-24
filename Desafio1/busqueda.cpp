#include "busqueda.h"
#include <iostream>
using namespace std;

// No se incluye ninguna otra librería, cumpliendo con la restricción.

int encontrarPista(const unsigned char* textoOriginal, const char* textoPista) {
    // Paso 1: Calcular la longitud de la pista y del texto original manualmente.
    int lenPista = 0;
    while (textoPista[lenPista] != '\0') {
        lenPista++;
    }

    // Si la pista está vacía, se considera encontrada por defecto.
    if (lenPista == 0) {
        return 1;
    }

    int lenOriginal = 0;
    while (textoOriginal[lenOriginal] != '\0') {
        lenOriginal++;
    }

    // Es imposible encontrar la pista si es más larga que el texto.
    if (lenPista > lenOriginal) {
        return 0;
    }

    // Paso 2: Iterar sobre el texto original para encontrar la pista.
    // Solo necesitamos iterar hasta el punto donde aún quepa la pista completa.
    for (int i = 0; i <= lenOriginal - lenPista; ++i) {

        // --- INICIO DE LA LÓGICA DE BÚSQUEDA "PALINDRÓMICA" ---

        bool esCoincidencia = true;
        int izquierda = 0;
        int derecha = lenPista - 1;

        // **Optimización Clave**: Como solicitaste, si en la primera iteración
        // (la comparación del carácter de más a la derecha) no hay coincidencia,
        // pasamos directamente al siguiente carácter del texto original.
        if (textoOriginal[i + derecha] != textoPista[derecha]) {
            continue; // Salta al siguiente valor de 'i' en el bucle for.
        }

        // Si el primer chequeo pasó, procedemos con la comparación completa
        // desde los extremos hacia el centro.
        while (izquierda <= derecha) {
            // 1. Compara el carácter de la derecha.
            esCoincidencia = true;
            if (textoOriginal[i + derecha] != textoPista[derecha]) {
                cout << textoOriginal[i + derecha] << "   " << textoPista[derecha] << endl;
                esCoincidencia = false;
                break; // Si no coincide, rompemos el bucle while.
            }

            // 2. Compara el carácter de la izquierda.
            if (textoOriginal[i + izquierda] != textoPista[izquierda]) {
                cout << textoOriginal[i + izquierda] << "  " << textoPista[izquierda] << endl;
                esCoincidencia = false;
                break; // Si no coincide, rompemos el bucle while.
            }

            // 3. Movemos los punteros hacia el centro.
            izquierda++;
            derecha--;
        }

        // Si el bucle while terminó y 'esCoincidencia' sigue siendo true,
        // significa que encontramos la pista completa.
        if (esCoincidencia) {
            return 1; // ¡Éxito!
        }
    }

    // Si el bucle for termina sin haber encontrado ninguna coincidencia, retornamos 0.
    return 0;
}

