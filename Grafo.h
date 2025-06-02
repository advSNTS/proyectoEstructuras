#ifndef GRAFO_H
#define GRAFO_H
#include "Arista.h"
#include <vector>

class Grafo
{
private:
    int numNodos;
    std::vector<std::vector<Arista>> adj;
public:
    Grafo(/* args */);
    Grafo(int altoImagen, int anchoImagen, std::vector<std::vector<int>> pixelesImagen);
    ~Grafo();
    int getNumeroNodos();
    std::vector<Arista> getVecinos(int nodoId);
    void imprimirGrafo();
};



#endif