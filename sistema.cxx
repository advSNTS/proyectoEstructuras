#include "sistema.h"
#include <iostream>
#include <fstream>
#include <sstream>

Sistema::Sistema(){
    this->imagenCargara = false;
}

void Sistema::cargar_imagen(std::string nombre){
    std::ifstream archivo(nombre);
    if(!archivo.is_open()){
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
        std::cout<<"Solo se recibe formato P2 o P3";
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
    std::cout<<"A y A"<<ancho<<" "<<altura<<std::endl;
    
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
            std::cout<<"Error: El archivo no tiene las lineas mencionadas";
            return;
        }
        if (linea.empty()) {
            std::cerr << "Error: Línea vacía en la fila " << i + 1 << std::endl;
            return;
        }
        std::vector<int> subvec;
        std::istringstream mat(linea);

        for(int j = 0; j<ancho; j++){
            int k;
            mat>>k;
            if(k>m_valor){
                std::cout<<"Error: se encontró un valor mayor al m_valor"<<std::endl;
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
    Imagen i(ancho, altura, m_valor, nombre, vec);
    this->imagen = i;
    this->imagenCargara = true;
}

void Sistema::info_imagen(){
    std::cout<<"Imagen cargada en memoria: "<<std::endl;
    this->imagen.mostrar();
}

void Sistema::cargar_volumen(std::string nombre, int n_im){
    if(n_im>99){
        std::cout<<"El número máximo de imagenes es 99"<<std::endl;
    }
    for (int i = 1; i <= n_im; i++)
    {
        std::cout<<i<<std::endl;
    }
    
}

void Sistema::info_volumen(){

}