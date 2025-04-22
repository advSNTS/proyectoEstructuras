#include "NodoHuffman.h"

NodoHuffman::NodoHuffman(int valor, int frecuencia){
    this->valor = valor;
    this->frecuencia = frecuencia;
    this->derecho = nullptr;
    this->izquierdo = nullptr;
}

NodoHuffman::NodoHuffman(NodoHuffman* izq, NodoHuffman* der){
    this->valor = -1;
    this->frecuencia = izq->getFrecuencia() + der->getFrecuencia();
    this->izquierdo = izq;
    this->derecho = der;
}

NodoHuffman::~NodoHuffman(){
    delete this->izquierdo;
    delete this->derecho;
}

int NodoHuffman::getFrecuencia(){
    return this->frecuencia;
}


NodoHuffman* NodoHuffman::getIzquierdo(){
    return this->izquierdo;
}


NodoHuffman* NodoHuffman::getDerecho(){
    return this->derecho;
}

int NodoHuffman::getValor(){
    return this->valor;
}