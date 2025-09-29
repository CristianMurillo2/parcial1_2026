#ifndef DESCOMPRESION_H
#define DESCOMPRESION_H

unsigned char* j_descomprimirRLE(unsigned char* j_dataComprimida, unsigned int j_tamComprimido, unsigned int& j_tamDescomprimido);
unsigned char* j_comprimirRLE(unsigned char* j_dataOriginal, unsigned int j_tamOriginal, unsigned int& j_tamComprimido);

#endif // DESCOMPRESION_H
