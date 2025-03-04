#include "volumen.h"

Volumen::Volumen(){
    this->cuenta = 0;
}

void Volumen::agregarImagen(Imagen imagen){
    this->volumen.push_back(imagen);
    this->cuenta++;
}