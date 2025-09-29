#include "encriptacion.h"
#include "lectura.h"
#include "descompresion.h"
#include "lz78.h"
#include "busqueda.h"

using namespace std;

int main()
{
    cout << "IMPORTANTE: los archivos deben de estar guardados en la carpeta build y tener el siguiente formato 'Encriptado#.txt'" << endl;
    cout << "Ingresa la cantidad de archivos que desea leer: " << endl;
    unsigned int cantArchivo = 3;
    /*
    while(!(cin >> cantArchivo)){
        cout << "Ingresa un numero valido (numero entero): ";
        cin.clear();
        cin.ignore();
    }
    */

    for(int cantArchivoAux = 1; cantArchivoAux <= cantArchivo; cantArchivoAux++){
    char* nombreDeArchivo = construirNombre("Encriptado", cantArchivoAux, ".txt");
    char* nombreDePista   = construirNombre("pista", cantArchivoAux , ".txt");


    long longitudEncriptado = obtenerLongitudArchivo(nombreDeArchivo);
    //cout << longitudEncriptado << endl << endl;
    char* textoEncriptado = leerArchivo(nombreDeArchivo, longitudEncriptado);
    //cout << textoEncriptado;

    long longitudPista = obtenerLongitudArchivo(nombreDePista);
    char* textoPista = leerArchivo(nombreDePista, longitudPista);
    //cout << textoPista;
    if (!textoEncriptado || !textoPista) {
        delete[] nombreDeArchivo;
        delete[] nombreDePista;
        continue;
    }
    delete[] nombreDeArchivo;
    delete[] nombreDePista;

    //control datos
    /*
    for (long i = 0; i < longitudEncriptado; i++) {
        cout << copiaDeDatos[i];
    }
    cout << endl;
    for (long i = 0; i < longitudPista; i++) {
        cout << textoPista[i];
    } */

    for(unsigned int rotacion = 1; rotacion < 8; rotacion++){
        for(unsigned int clave = 1; clave < 256 ; clave++){
            //cout << endl<<clave << endl;
            unsigned char* textoEncrip = static_cast<unsigned char*>(reinterpret_cast<void*>(textoEncriptado));
            unsigned char * desencriptado = j_desencriptarMensaje(textoEncrip, longitudEncriptado, (clave), rotacion); // clave+1
            //cout << desencriptado;
            quitarEspaciosEnMemoria(desencriptado);
            unsigned int tamano = longitudE(desencriptado);

            for(int i=0; i < tamano ; i++){
                if(65 <= (unsigned int)desencriptado[i] && (unsigned int)desencriptado[i]<=90){
                    desencriptado[i] = desencriptado[i] + 32;
                }

                if(33 <= (unsigned int)desencriptado[i] && (unsigned int)desencriptado[i]<=42){
                    desencriptado[i] = desencriptado[i] + 16;
                }


            }
            //RLE
            unsigned int tamanoDescomprimido = 0;
            unsigned char* textoOriginal = j_descomprimirRLE(desencriptado, tamano, tamanoDescomprimido);
            //cout << clave << "      " << rotacion << endl;
            //cout << desencriptado;
            //cout << textoOriginal;
            int correcto = encontrarPista(textoOriginal, textoPista);
            if(correcto == 1){
                cout << endl <<"El texto original antes de ser comprimido y encriptado es: " << endl;
                cout << textoOriginal << endl;
                delete textoOriginal;
                cout << endl << "La clave de la encriptacion es: " << clave;
                cout << endl << "La rotacion utilizada de la compresion es: " << rotacion << endl;
                cout << "El metodo de compresion fue :" << " RLE" << endl;
                cin.get();
                if(cantArchivoAux == cantArchivo){
                    return 0;
                }

            }
            else{
                delete textoOriginal;
            }
            //LZ78
            //unsigned char* textoOriginal=lz78_decompress(desencriptado,tamano);
            //cout<<textoOriginal;
        }        
    }

cin.get();

}
    return 0;
}

