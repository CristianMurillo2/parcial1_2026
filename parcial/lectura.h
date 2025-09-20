#ifndef LECTURA_H
#define LECTURA_H
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;
void lectura();
void imprimirbinario(unsigned char c);
long obtenerLongitudArchivo(const char *nombrearchivo);
char *leerArchivo(const char* nombreArchivo, long longitud);
#endif // LECTURA_H
