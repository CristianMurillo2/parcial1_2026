#include "lectura.h"

void lectura()
{
    ifstream archivo("texto.txt",ios::in);
    cout << "Directorio actual: " << filesystem::current_path() << endl; //comprobar donde esta el ejecutable
    const char* nombre = "Encriptado3.txt";
    long longitud = obtenerLongitudArchivo(nombre);
    if (longitud == -1) exit(1);

    cout << "Longitud del archivo: " << longitud << " bytes" << endl;

    char* contenido = leerArchivo(nombre, longitud);

    if (contenido) {
        cout << "\n--- Mensaje original ---\n";
        for (long i = 0; i < longitud; i++) {
            cout << contenido[i];
        }
        cout << "\n";
        cout << "Contenido en binario:" << endl;
        for (long i = 0; i < longitud; i++) {
            imprimirbinario(static_cast<unsigned char>(contenido[i]));
            cout << " ";
        }
        cout << endl;

        delete[] contenido;
    }
}

void imprimirbinario(unsigned char c)
{
    for (int i = 7; i >= 0; i--) {
        cout << ((c >> i) & 1);
    }
}

long obtenerLongitudArchivo(const char *nombrearchivo)
{
    ifstream archivo(nombrearchivo, ios::binary | ios::ate);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return -1;
    }
    long longitud = archivo.tellg();
    archivo.close();
    return longitud;
}

char *leerArchivo(const char *nombreArchivo, long longitud)
{
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return nullptr;
    }
    char* buffer = new char[longitud]; // se guarda tal cual en binario
    archivo.read(buffer, longitud);
    archivo.close();
    return buffer;
}

