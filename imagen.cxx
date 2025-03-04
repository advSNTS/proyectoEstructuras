#include "imagen.h"
#include <iostream>
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
    std::cout<<this->nombreArchivo<<"   Ancho: "<<this->ancho<<". Alto: "<<this->alto<<". M_pixel: "<<this->m_pixel<<std::endl<<". Imagen: "<<std::endl;
    for(std::vector<std::vector<int>>::iterator it = this->imagen.begin(); it != this->imagen.end(); it++){
        for(std::vector<int>::iterator eso = it->begin(); eso != it->end(); eso++){
            std::cout<<*eso<<" ";
        }
        std::cout<<std::endl;
    }
}