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

        j_byteActual = j_byteActual ^ (unsigned char)j_claveK; //(nos ayuda a verlo como un char de 1 byte)

        j_byteActual = j_rotarDerecha(j_byteActual, j_rotacionN);

        j_datosDesencriptados[i] = j_byteActual;
    }

    return j_datosDesencriptados;
}
