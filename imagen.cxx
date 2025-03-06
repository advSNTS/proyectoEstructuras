#include "imagen.h"
#include <iostream>
#include <fstream>
Imagen::Imagen(){

}

Imagen::Imagen(int ancho, int alto, int m_pixel, std::string nombreArchivo, std::vector<std::vector<int>> imagen){
    this->ancho = ancho;
    this->alto = alto;
    this->m_pixel = m_pixel;
    this->nombreArchivo = nombreArchivo;
    this-> imagen = imagen;
}

void Imagen::mostrar(){
    std::cout<<this->nombreArchivo<<"   Ancho: "<<this->ancho<<". Alto: "<<this->alto<<". M_pixel: "<<this->m_pixel<<std::endl;
    /*
    for(std::vector<std::vector<int>>::iterator it = this->imagen.begin(); it != this->imagen.end(); it++){
        for(std::vector<int>::iterator eso = it->begin(); eso != it->end(); eso++){
            std::cout<<*eso<<" ";
        }
        std::cout<<std::endl;
    }
    */
}


void Imagen::imprimir() {
    std::ofstream salida("salida.pgm");
    for (std::vector<std::vector<int>>::iterator it = this->imagen.begin(); it != this->imagen.end(); ++it) {
        std::vector<int>::iterator eso = it->begin();
        if (eso != it->end()) { 
            salida << *eso; 
            ++eso;
        }
        for (; eso != it->end(); ++eso) {
            salida << " " << *eso; 
        }
        salida << std::endl;
    }
}

int Imagen::getAlto(){
    return this->alto;
}

int Imagen::getAncho(){
    return this->ancho;
}

const std::vector<std::vector<int>>& Imagen::getImagen() const{
    return this->imagen;
}

int Imagen::getAltoConstante() const{
    return this->alto;
}

int Imagen::getAnchoConstante() const{
    return this->ancho;
}