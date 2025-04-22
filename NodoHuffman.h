#ifndef NODOHUFFMAN_H
#define NODOHUFFMAN_H

class NodoHuffman
{
private:
    int valor;
    int frecuencia;
    NodoHuffman* izquierdo;
    NodoHuffman* derecho;
public:
    NodoHuffman(int valor, int frecuencia);
    NodoHuffman(NodoHuffman* izq, NodoHuffman* der);
    ~NodoHuffman();
    int getFrecuencia();

    NodoHuffman* getIzquierdo();
    NodoHuffman* getDerecho();
    int getValor();

};

#endif