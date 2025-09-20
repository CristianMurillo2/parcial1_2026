#include "lectura.h"

void lectura()
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
