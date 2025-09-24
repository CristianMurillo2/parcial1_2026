#ifndef BUSQUEDA_H
#define BUSQUEDA_H

/**
 * @brief Busca una pista en un texto original utilizando un método de comparación "palindrómico".
 * * Compara los caracteres de la pista desde los extremos hacia el centro. Si el primer
 * carácter (el último de la pista) no coincide, salta a la siguiente posición
 * del texto original inmediatamente.
 * * @param textoOriginal El texto completo donde se realizará la búsqueda.
 * @param textoPista La secuencia de caracteres a encontrar.
 * @return Retorna 1 si se encuentra la pista, de lo contrario retorna 0.
 */
int encontrarPista(const unsigned char* textoOriginal, const char* textoPista);

#endif // BUSQUEDA_H
