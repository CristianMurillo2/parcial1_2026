#ifndef LECTURA_H
#define LECTURA_H
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;
void lectura();
void imprimirbinario(const char *binario);
long obtenerLongitudArchivo(const char *nombrearchivo);
char *leerArchivo(const char* nombreArchivo, long longitud);
char *convertirABinario(const char* contenido, long longitud);

#endif // LECTURA_H
