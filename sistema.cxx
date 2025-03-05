#include "sistema.h"
#include <iostream>
#include <fstream>
#include <sstream>

Sistema::Sistema(){
    this->imagenCargada = false;
    this->volumenCargado = false;
}

void Sistema::cargar_imagen(std::string nombre, bool volumen){
    if(!volumen && this->imagenCargada){
        std::cout<<"UNa imagen ya fue cargada y esta será sobreescrita."<<std::endl;
    }
    std::ifstream archivo(nombre);
    if(!archivo.is_open()){
        std::cout<<"La imagen no ha podido ser cargada. No existe el archivo '"<<nombre<<"' o no está en el directorio actual."<<std::endl;
        return;
    }
    std::stringstream imagen;
    std::string linea;
    imagen<<archivo.rdbuf();
    archivo.close();


    std::string tipo;
    getline(imagen, tipo);
    std::cout<<"Tipo: '"<<tipo<<"'"<<std::endl;
    if(tipo != "P2" && tipo != "P3"){
        std::cout<<"La imagen no ha podido ser cargada. Solo se recibe formato P2 o P3";
        return;
    }

    while (getline(imagen, linea)) {
        if (linea.empty() || linea[0] != '#') {
            break;
        }
    }
    int ancho, altura;
    std::stringstream flujo(linea);
    flujo >> ancho >> altura;
    if(volumen){
        if(!volumenCargado){
            this->anchoControlVolumen = ancho;
            this->altoControlVolumen = altura;
        }
        if(this->anchoControlVolumen != ancho){
            std::cout<<"NO se pudo cargar el volumen. existe un ancho diferente en el archivo '"<<nombre<<"'"<<std::endl;
            return;
        }
        if(this->altoControlVolumen!=altura){
            std::cout<<"NO se pudo cargar el volumen. existe un alto diferente en el archivo '"<<nombre<<"'"<<std::endl;
            return;
        }
    }
    
    std::cout<<"Ancho y Aaltura: "<<ancho<<", "<<altura<<std::endl;
    
    while (getline(imagen, linea)) {
        if (linea.empty() || linea[0] != '#') {
            break;
        }
    }

    flujo.clear();
    flujo.str(linea);
    int m_valor;
    flujo>>m_valor;
    std::cout<<"M_valor: "<<m_valor<<std::endl;

    std::vector<std::vector<int>> vec;

    for(int i=0; i<altura; i++){
        if(!getline(imagen, linea)){
            std::cout<<"La imagen no ha podido ser cargada. El archivo no tiene las lineas mencionadas"<<std::endl;
            return;
        }
        if (linea.empty()) {
            std::cout <<"La imagen no ha podido ser cargada. Línea vacía en la fila " << i + 1 << std::endl;
            return;
        }
        std::vector<int> subvec;
        std::istringstream mat(linea);

        for(int j = 0; j<ancho; j++){
            int k;
            mat>>k;
            if(k>m_valor){
                std::cout<<"La imagen no ha podido ser cargada. Se encontró un valor mayor al m_valor"<<std::endl;
                return;
            }
            subvec.push_back(k);
        }
        vec.push_back(subvec);
    }
    /*
    for(std::vector<std::vector<int>>::iterator it = vec.begin(); it != vec.end(); it++){
        std::cout<<std::endl;
        for(std::vector<int>::iterator eso = it->begin(); eso != it->end(); eso++){
            std::cout<<*eso<<" ";
        }
    }
    std::cout<<std::endl;
    */
    if(!volumen){
        std::cout<<"La imagen '"<<nombre<<"' ha sido cargada."<<std::endl;
    }
    Imagen i(ancho, altura, m_valor, nombre, vec);
    if(!volumen){
        this->imagen = i;
        this->imagenCargada = true;
    }
    if(volumen){
        this->volumen.agregarImagen(i);
        this->volumenCargado = true;
        std::cout<<"Imagen de volumen '"<<nombre<<"' cargado."<<std::endl;
    }
}



void Sistema::info_imagen(){
    if(!this->imagenCargada){
        std::cout<<"Una imagen aun no ha sido cargada."<<std::endl;
        return;
    }
    std::cout<<"Imagen cargada en memoria: "<<std::endl;
    this->imagen.mostrar();
}

void Sistema::cargar_volumen(std::string nombre, int n_im){
    if(this->volumenCargado){
        std::cout<<"Un volumen ya fue cargado y este será sobreescrito."<<std::endl;
    }
    if(n_im>99){
        std::cout<<"El número máximo de imagenes es 99"<<std::endl;
        return;
    }
    if(n_im<1){
        std::cout<<"El volumen no pudo ser cargado. El número minimo de imagenes es 1"<<std::endl;
        return;
    }
    if(nombre.find('.')==std::string::npos){
        std::cout<<"El volumen no pudo ser cargado. Falta la extension '.' del archivo"<<std::endl;
    }
    std::string nombreBase = nombre.substr(0, nombre.find('.'));
    std::string extension = nombre.substr(nombre.find('.'));
    std::cout<<nombreBase<<std::endl<<extension<<std::endl;
    std::string archivo = "";
    for(int i=1; i<n_im+1; i++){
        if(i<10){ //se debe concatenar el 0;
            archivo = nombreBase + '0' + std::to_string(i) + extension;
        }
        else{
            archivo = nombreBase + std::to_string(i) + extension;
        }
        cargar_imagen(archivo, true);
    }
}

void Sistema::info_volumen(){
    if(!this->volumenCargado){
        std::cout<<"Aun no se ha cargado un volumen."<<std::endl;
        return;
    }
    this->volumen.infoVolumen();
}