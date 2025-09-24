#include "encriptacion.h"
#include "lectura.h"
#include "descompresion.h"
#include "lz78.h"
#include "busqueda.h"
using namespace std;

int main()
{
    const char* nombreDeArchivo = "Encriptado1.txt";
    const char* nombreDePista = "pista1.txt";

    long longitudEncriptado = obtenerLongitudArchivo(nombreDeArchivo);
    char* textoEncriptado = leerArchivo(nombreDeArchivo, longitudEncriptado);

    long longitudPista = obtenerLongitudArchivo(nombreDePista);
    char* textoPista = leerArchivo(nombreDePista, longitudPista);
    cout << textoPista;

    //control datos
    /*
    for (long i = 0; i < longitudEncriptado; i++) {
        cout << copiaDeDatos[i];
    }
    cout << endl;
    for (long i = 0; i < longitudPista; i++) {
        cout << textoPista[i];
    } */
    //RLE
    for(unsigned int rotacion = 3; rotacion < 4; rotacion++){
        for(unsigned int clave = 91; clave < 92 ; clave++){
            unsigned char* textoEncrip = static_cast<unsigned char*>(reinterpret_cast<void*>(textoEncriptado));
            unsigned char * desencriptado = j_desencriptarMensaje(textoEncrip, longitudEncriptado, (clave), rotacion); // clave+1
            quitarEspaciosEnMemoria(desencriptado);
            unsigned int tamano = longitudE(desencriptado);

            for(int i=0; i < tamano ; i++){
                if(i % 2 == 0){
                    desencriptado[i] = desencriptado[i] + 16;
                }
                else{
                    desencriptado[i] = desencriptado[i] + 32;
                }
            }
            unsigned int tamanoDescomprimido = 0;

            unsigned char* textoOriginal = j_descomprimirRLE(desencriptado, tamano, tamanoDescomprimido);
            //cout << clave << "      " << rotacion << endl;
            //cout << desencriptado;
            //cout << textoOriginal;

            int correcto = encontrarPista(textoOriginal, textoPista);
            if(correcto == 1){
                cout << "El texto original antes de ser comprimido y encriptado es: " << endl;
                cout << textoOriginal << endl;
                cout << endl << "La clave de la encriptacion es: " << clave;
                cout << endl << "La rotacion utilizada de la compresion es: " << rotacion;
                cin.get();
                return 0;
            }
        }        
    }




cin.get();


    return 0;
}

