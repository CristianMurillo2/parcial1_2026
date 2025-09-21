#include "descompresion.h"

void j_copiarMemoria(unsigned char* j_destino, unsigned char* j_fuente, unsigned int j_tamano) {
    for (unsigned int i = 0; i < j_tamano; ++i) {
        j_destino[i] = j_fuente[i];
    }
}

unsigned char* j_descomprimirRLE(unsigned char* j_dataComprimida, unsigned int j_tamComprimido, unsigned int& j_tamDescomprimido)
{
    unsigned int j_capSalida = j_tamComprimido * 10;
    unsigned char* j_salida = new unsigned char[j_capSalida];
    j_tamDescomprimido = 0;

    for (unsigned int i = 0; i < j_tamComprimido; i += 2)
    {
        unsigned char j_repeticiones = j_dataComprimida[i];
        unsigned char caracter = j_dataComprimida[i + 1];

        if (j_tamDescomprimido + j_repeticiones > j_capSalida)
        {
            unsigned int j_nuevaCapacidad = j_capSalida * 2;
            unsigned char* j_nuevoSalida = new unsigned char[j_nuevaCapacidad];

            j_copiarMemoria(j_nuevoSalida, j_salida, j_tamDescomprimido);
            delete[] j_salida;

            j_salida = j_nuevoSalida;
            j_capSalida = j_nuevaCapacidad;
        }

        for (int j = 0; j < j_repeticiones; ++j)
        {
            j_salida[j_tamDescomprimido] = caracter;
            j_tamDescomprimido++;
        }
    }

    return j_salida;
}

unsigned char* j_comprimirRLE(unsigned char* j_dataOriginal, unsigned int j_tamOriginal, unsigned int& j_tamComprimido)
{
    if (j_tamOriginal == 0)
    {
        j_tamComprimido = 0;
        return nullptr;
    }

    unsigned int j_capacidadSalida = j_tamOriginal * 2;
    unsigned char* j_salida = new unsigned char[j_capacidadSalida];
    j_tamComprimido = 0;

    unsigned int i = 0;
    while (i < j_tamOriginal)
    {
        unsigned char j_caracterActual = j_dataOriginal[i];
        unsigned char j_conteo = 0;
        unsigned int k = i;
        while (k < j_tamOriginal && j_dataOriginal[k] == j_caracterActual && j_conteo < 255)
        {
            j_conteo++;
            k++;
        }

        j_salida[j_tamComprimido] = j_conteo;
        j_tamComprimido++;
        j_salida[j_tamComprimido] = j_caracterActual;
        j_tamComprimido++;
        i += j_conteo;
    }

    return j_salida;
}
