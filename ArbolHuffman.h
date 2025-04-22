#ifndef ARBOLHUFFMAN_H
#define ARBOLHUFFMAN_H
#include "NodoHuffman.h"
#include <map>
#include <iostream>
class ArbolHuffman
{
private:
    NodoHuffman* raiz;
public:
    ArbolHuffman(/* args */);
    ~ArbolHuffman();
    void construirDesdeHistograma(const std::map<int, int>& histograma);
    void generarCodigos(std::map<int, std::string>& codigos);
    void generarCodigosRec(NodoHuffman* nodo, const std::string& camino, std::map<int, std::string>& codigos);
    NodoHuffman* getRaiz();
};

#endif