#include "volumen.h"

Volumen::Volumen(){
    this->cuenta = 0;
}

void Volumen::agregarImagen(Imagen imagen){
    this->volumen.push_back(imagen);
    this->cuenta++;
}

void Volumen::infoVolumen(){
    std::cout<<"Nombre base: '"<<this->nombreBase<<"' tamanio: '"<<this->cuenta<<"' Ancho: '"<<this->volumen[0].getAnchoConstante()<<"' Alto: ";
    std::cout<<this->volumen[0].getAltoConstante()<<"'"<<std::endl;
    
    /*
    for(std::vector<Imagen>::iterator it = this->volumen.begin(); it!=this->volumen.end(); it++){
        it->mostrar();
        std::cout<<std::endl<<"-----------------------"<<std::endl;
    }
    */
}

int Volumen::getCuenta(){
    return this->cuenta;
}

const std::vector<Imagen>& Volumen::getVolumen() const{
    return this->volumen;
}

void Volumen::setNombreBase(std::string nombre){
    this->nombreBase = nombre;
}