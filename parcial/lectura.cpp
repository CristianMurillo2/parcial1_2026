#include "lectura.h"

void lectura()
{
    const char* nombre = "Encriptado3.txt"; // archivo de texto
    long longitud = obtenerLongitudArchivo(nombre);
    if (longitud == -1) exit(1);
    ifstream archivo("texto.txt",ios::in); // Abrir el archivo en modo lectura
    cout << "Directorio actual: " << filesystem::current_path() << endl; //comprobar donde esta el ejecutable
    cout << "Longitud del archivo: " << longitud << " bytes" << endl;
    char* contenido = leerArchivo(nombre, longitud);
    if (contenido) {
        cout << "\n--- Mensaje original ---\n";
        for (long i = 0; i < longitud; i++) {
            cout << contenido[i];
        }
        char *binario = convertirABinario(contenido, longitud);
        cout << "\n";
        cout << "Contenido en binario:" << endl;
        imprimirbinario(binario);
        cout << endl;
        delete[] contenido; // liberar memoria
        delete[] binario;
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
    char* buffer = new char[longitud]; // se guarda tal cual en binario
    archivo.read(buffer, longitud);
    archivo.close();
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

char *convertirABinario(const char *contenido, long longitud) //falta liberar la memoria de binario[]
{
    long tamanoBinario = longitud * 9;
    char* binario = new char[tamanoBinario + 1]; // +1 para '\0'
    long pos = 0;
    for (long i = 0; i < longitud; i++) {
        unsigned char c = static_cast<unsigned char>(contenido[i]);
        for (int j = 7; j >= 0; j--) {
            binario[pos++] = ((c >> j) & 1) ? '1' : '0';
        }
        binario[pos++] = ' ';
    }
    binario[pos] = '\0';
    return binario;
}
