#include "lectura.h"

void lectura()
{
    const char* nombre = "pista1.txt";
    long longitud = obtenerLongitudArchivo(nombre);
    if (longitud == -1) exit(1);
    ifstream archivo("texto.txt",ios::in);
    cout << "Directorio actual: " << filesystem::current_path() << endl; //comprobar donde esta el ejecutable
    cout << "Longitud del archivo: " << longitud << " bytes" << endl;
    char* contenido = leerArchivo(nombre, longitud);
    if (contenido) {
        cout << "\n--- Mensaje original ---\n";
        for (long i = 0; i < longitud; i++) {
            cout << contenido[i];
        }
        /*char *binario = convertirABinario(contenido, longitud);
        cout << "\n";
        cout << "Contenido en binario:" << endl;
        imprimirbinario(binario);*/
        cout << endl;
        delete[] contenido; // liberar memoria
        //delete[] binario;
    }
}

void imprimirbinario(const char *binario)
{
    cout << "\n--- Mensaje en binario ---\n";
    cout << binario << endl;
}

long obtenerLongitudArchivo(const char *nombrearchivo)
{
    ifstream archivo(nombrearchivo, ios::binary | ios::ate);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return -1;
    }
    long longitud = archivo.tellg(); // posición actual = tamaño en bytes
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
    char* buffer = new char[longitud+1]; // se guarda tal cual en binario
    archivo.read(buffer, longitud);
    archivo.close();
    buffer[longitud] = '\0';
    return buffer;
}

void leer()
{
    ifstream archivo("texto.txt",ios::in); // Abrir el archivo en modo lectura
    cout << "Directorio actual: " << filesystem::current_path() << endl; //comprobar donde esta el ejecutable

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        exit(1);
    }

    string linea;
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }
    archivo.close();
}

char* obtenerBytes(const char* contenido, long longitud) {
    if (longitud <= 0 || contenido == nullptr) {
        return nullptr;
    }
    char* copiaDeBytes = new char[longitud];
    for (long i = 0; i < longitud; i++) {
        copiaDeBytes[i] = contenido[i];
    }

    return copiaDeBytes;
}

void intAChars(int num, char* buffer, int& pos) {
    char temp[10];
    int t = 0;
    do {
        temp[t++] = (num % 10) + '0';
        num /= 10;
    } while (num > 0);
    for (int i = t - 1; i >= 0; i--) {
        buffer[pos++] = temp[i];
    }
}

char* construirNombre(const char* base, int num, const char* extension) {
    char* nombre = new char[50];
    int pos = 0;
    for (int i = 0; base[i] != '\0'; i++) {
        nombre[pos++] = base[i];
    }
    intAChars(num, nombre, pos);
    for (int i = 0; extension[i] != '\0'; i++) {
        nombre[pos++] = extension[i];
    }

    nombre[pos] = '\0';
    return nombre;
}
