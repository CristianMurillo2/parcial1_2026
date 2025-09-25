#include "encriptacion.h"

unsigned char j_rotarDerecha(unsigned char j_byte, int j_n) {
    unsigned char j_parteDerecha = j_byte >> j_n;
    unsigned char j_parteIzquierda = j_byte << (8 - j_n);
    return j_parteDerecha | j_parteIzquierda; //( | operacion or)
}


unsigned char* j_desencriptarMensaje(unsigned char* j_dataEncriptada, unsigned int j_tamano, int j_claveK, int j_rotacionN)
{
    unsigned char* j_datosDesencriptados = new unsigned char[j_tamano];

    for (unsigned int i = 0; i < j_tamano; ++i) {
        unsigned char j_byteActual = j_dataEncriptada[i];

        j_byteActual = j_byteActual ^ (unsigned char)j_claveK;

        j_byteActual = j_rotarDerecha(j_byteActual, j_rotacionN);

        j_datosDesencriptados[i] = j_byteActual;
    }

    return j_datosDesencriptados;
}

char* convertirABin(int numero) {
    char* binario = new char[9];
    unsigned char byte = static_cast<unsigned char>(numero);

    for (int i = 0; i < 8; i++) {
        if ((byte & (128 >> i)) != 0) {
            binario[i] = '1';
        } else {
            binario[i] = '0';
        }
    }
    binario[8] = '\0';
    return binario;
}


void quitarEspaciosEnMemoria(unsigned char* datos) {
    if (datos == nullptr) {
        return;
    }

    int indiceEscritura = 0;
    for (int indiceLectura = 0; datos[indiceLectura] != '\0'; indiceLectura++) {
        if (datos[indiceLectura] != ' ') {
            datos[indiceEscritura] = datos[indiceLectura];
            indiceEscritura++;
        }
    }

    datos[indiceEscritura] = '\0';
}
