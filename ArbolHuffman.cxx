#include "ArbolHuffman.h"
#include <queue>



struct ComparadorNodos {
    bool operator()(NodoHuffman* a, NodoHuffman* b) {
        return a->getFrecuencia() > b->getFrecuencia();
    }
};


ArbolHuffman::ArbolHuffman(){
    this->raiz = nullptr;
}

ArbolHuffman::~ArbolHuffman(){
    if(this->raiz!=nullptr){
        delete this->raiz;
        this->raiz = nullptr;
    }
}




NodoHuffman* ArbolHuffman::getRaiz(){
    return this->raiz;
}

void ArbolHuffman::construirDesdeHistograma(const std::map<int, int>& histograma) {
    std::priority_queue<NodoHuffman*, std::vector<NodoHuffman*>, ComparadorNodos> cola;

    for (std::map<int, int>::const_iterator it = histograma.begin(); it != histograma.end(); ++it) {
        NodoHuffman* nodo = new NodoHuffman(it->first, it->second);
        cola.push(nodo);
    }

    while (cola.size() > 1) {
        NodoHuffman* nodo1 = cola.top(); cola.pop();
        NodoHuffman* nodo2 = cola.top(); cola.pop();

        NodoHuffman* combinado = new NodoHuffman(nodo1, nodo2);
        cola.push(combinado);
    }

    if (!cola.empty()) {
        raiz = cola.top();
    }
}


void ArbolHuffman::generarCodigos(std::map<int, std::string>& codigos){
    generarCodigosRec(this->raiz, "", codigos);
}


void ArbolHuffman::generarCodigosRec(NodoHuffman* nodo, const std::string& camino, std::map<int, std::string>& codigos){
    if(nodo == nullptr){
        return;
    }

    if(nodo->getFrecuencia()>0){
        codigos[nodo->getValor()]=camino;
    }

    generarCodigosRec(nodo->getIzquierdo(), camino + "0", codigos);
    generarCodigosRec(nodo->getDerecho(), camino + "1", codigos);
}

