#include "encriptacion.h"
#include "lectura.h"
#include "descompresion.h"
#include "lz78.h"
using namespace std;

int main()
{
    const char* nombreDeArchivo = "Encriptado3.txt";
    const char* nombreDePista = "pista1.txt";

    long longitudEncriptado = obtenerLongitudArchivo(nombreDeArchivo);
    char* textoEncriptado = leerArchivo(nombreDeArchivo, longitudEncriptado);

    long longitudPista = obtenerLongitudArchivo(nombreDePista);
    char* textoPista = leerArchivo(nombreDePista, longitudPista);

    //control datos
    /*
    for (long i = 0; i < longitudEncriptado; i++) {
        cout << copiaDeDatos[i];
    }
    cout << endl;
    for (long i = 0; i < longitudPista; i++) {
        cout << textoPista[i];
    } */

    for(unsigned int rotacion = 3; rotacion < 4; rotacion++){
        for(unsigned int clave = 65; clave < 66 ; clave++){
            //char* claveBinario = convertirABin(clave);
            //codigo en binario
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
            unsigned char* texto_original = j_descomprimirRLE(desencriptado, tamano, tamanoDescomprimido);
            cout << clave << "      " << rotacion << endl;
            cout << desencriptado << endl;
            cout << texto_original;



            //XOR con clave y codigo
            //volver de bin a char
            //descomprimir por ambos metodos
            //comparar
            //liberar memoria cuando sea necesario
        }        

    }




cin.get();


    return 0;
}

