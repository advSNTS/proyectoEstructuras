#include "Arista.h"

Arista::Arista(){

}

Arista::Arista(int destinoId, int costo){
    this->destinoId = destinoId;
    this->costo = costo;
}

Arista::~Arista(){

}

int Arista::getDestinoId(){
    return this->destinoId;
}

int Arista::getCosto(){
    return this->costo;
}

