
#include "lectura.h"

using namespace std;

int main()
{
    const char* nombreDeArchivo = "Encriptado1.txt";
    const char* nombreDePista = "pista1.txt";

    long longitudEncriptado = obtenerLongitudArchivo(nombreDeArchivo);
    char* textoEncriptado = leerArchivo(nombreDeArchivo, longitudEncriptado);

    long longitudPista = obtenerLongitudArchivo(nombreDePista);
    char* textoPista = leerArchivo(nombreDePista, longitudPista);

    //control datos
    /*
    for (long i = 0; i < longitudEncriptado; i++) {
        cout << textoEncriptado[i];
    }
    cout << endl;
    for (long i = 0; i < longitudPista; i++) {
        cout << textoPista[i];
    }
    */

    for(unsigned int rotacion = 1; rotacion < 8; rotacion++){
        for(unsigned int clave = 1; clave < 256; clave++){
            char* claveBinario = convertirABinario(clave);
        }
        cout << claveBinario;
    }







    return 0;
}

