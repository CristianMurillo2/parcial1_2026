#include "lectura.h"
#include "descompresion.h"

using namespace std;

int main()
{
    lectura();

    unsigned char datos_comprimidos[] = {
        5, 'a',
        4, 'b',
        100, 'c',
        7, 'v',
        12, 'p'
    };

    unsigned int tamano_comprimido = sizeof(datos_comprimidos);
    unsigned int tamano_descomprimido = 0;

    unsigned char* texto_original = j_descomprimirRLE(datos_comprimidos, tamano_comprimido, tamano_descomprimido);

    if (texto_original != nullptr) {
        std::cout << "Descompresion exitosa!" << std::endl;
        std::cout << "Tamano descomprimido: " << tamano_descomprimido << std::endl;

        std::cout << "Texto original: ";
        for (unsigned int i = 0; i < tamano_descomprimido; ++i) {
            std::cout << texto_original[i];
        }
        std::cout << std::endl;

        delete[] texto_original;
    }

    return 0;
}
