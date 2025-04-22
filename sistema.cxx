#include "sistema.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cstdint>
#include "NodoHuffman.h"

Sistema::Sistema(){
    this->imagenCargada = false;
    this->volumenCargado = false;
}


void Sistema::codificarImagen(std::string nombre){
    if(!this->imagenCargada){
        std::cout<<"No existe una imagen cargada en memoria."<<std::endl;
        return;
    }
    const std::vector<std::vector<int>>& ima = this->imagen.getImagen();
    std::map<int, int> histograma;
    for(std::vector<std::vector<int>>::const_iterator it = ima.begin(); it != ima.end(); it++){
        for(std::vector<int>::const_iterator eso = it->begin(); eso!= it->end(); eso++){
            histograma[*eso]++;
        }
    }
    for (const auto& par : histograma) {
        std::cout << "Valor: " << par.first << " aparece " << par.second << " veces\n";
    }

    ArbolHuffman arbolHuffman;
    arbolHuffman.construirDesdeHistograma(histograma);

    std::map<int, std::string> codigos;
    arbolHuffman.generarCodigos(codigos);

    std::cout << "Códigos de Huffman:" << std::endl;
    for (const auto& par : codigos) {
        std::cout << "Valor: " << par.first << " -> Código: " << par.second << std::endl;
    }

    std::ofstream archivo(nombre, std::ios::binary);
    if(!archivo.is_open()){
        std::cout<<"Hubo un error al abrir el archivo.";
        return;
    }
    unsigned short W = this->imagen.getAncho();
    unsigned short H = this->imagen.getAlto();
    unsigned char M = this->imagen.getMpixel();

    archivo.write(reinterpret_cast<const char*>(&W), sizeof(W));
    archivo.write(reinterpret_cast<const char*>(&H), sizeof(H));
    archivo.write(reinterpret_cast<const char*>(&M), sizeof(M));


    for(int i=0; i<=this->imagen.getMpixel(); i++){
        unsigned long frecuencia = 0;
        if(histograma.count(i)){
            frecuencia = histograma.at(i);
        }
        archivo.write(reinterpret_cast<const char*>(&frecuencia), sizeof(unsigned long));
    }

    std::string cadenaDeBits;
    for (const auto& fila : ima) {
        for (int valorPixel : fila) {
            if (codigos.count(valorPixel)) {
                cadenaDeBits += codigos.at(valorPixel);
            } else {
                std::cerr << "Error: No se encontró código Huffman para el valor de píxel: " << valorPixel << std::endl;
                archivo.close(); 
                return;
            }
        }
    }

    unsigned int totalBitsCodificados = cadenaDeBits.length();
    archivo.write(reinterpret_cast<const char*>(&totalBitsCodificados), sizeof(totalBitsCodificados));

    std::vector<unsigned char> bytes;
    unsigned char actual = 0;
    int contador = 0;

    for (char bit : cadenaDeBits) { 
        actual <<= 1;
        if (bit == '1') {
            actual |= 1;
        }
        contador++;

        if (contador == 8) {
            bytes.push_back(actual);
            actual = 0;
            contador = 0;
        }
    }

    if (contador > 0) {
        actual <<= (8 - contador); 
        bytes.push_back(actual);
    }


    if (!bytes.empty()) {
         archivo.write(reinterpret_cast<const char*>(&bytes[0]), bytes.size());
    }

    archivo.close();
    std::cout << "Imagen codificada exitosamente en " << nombre << std::endl;
}

void Sistema::decodificarImagen(std::string archivohuff, std::string nombrepgm){
    std::ifstream archivo(archivohuff, std::ios::binary);
    if (!archivo.is_open()) {
        std::cout << "El archivo "<< archivohuff <<" no ha podido ser abierto para decodificar."<< std::endl;
        return;
    }

    unsigned short W, H;
    unsigned char M;

    archivo.read(reinterpret_cast<char*>(&W), sizeof(W));
    archivo.read(reinterpret_cast<char*>(&H), sizeof(H));
    archivo.read(reinterpret_cast<char*>(&M), sizeof(M));

    if (!archivo) {
         std::cout << "El archivo "<< archivohuff <<" no ha podido ser abierto para decodificar."<< archivohuff << std::endl;
         archivo.close();
         return;
    }

    std::map<int, int> histograma;
    for (int i = 0; i <= M; ++i) {
        unsigned long frecuencia;
        archivo.read(reinterpret_cast<char*>(&frecuencia), sizeof(unsigned long));
        if (!archivo) {
             std::cout << "El archivo "<< archivohuff <<" no ha podido ser abierto para decodificar."<< archivohuff << std::endl;
             archivo.close();
             return;
        }
        if (frecuencia > 0) {
            histograma[i] = static_cast<int>(frecuencia);
            if (histograma[i] < 0) {
                 std::cout << "El archivo "<< archivohuff <<" no ha podido ser abierto para decodificar." << i << std::endl;
            }
        }
    }

    unsigned int cantidadBits = 0;
    archivo.read(reinterpret_cast<char*>(&cantidadBits), sizeof(cantidadBits));
     if (!archivo) {
         std::cout << "El archivo "<< archivohuff <<" no ha podido ser abierto para decodificar."<< archivohuff << std::endl;
         archivo.close();
         return;
     }

    ArbolHuffman arbol;
    arbol.construirDesdeHistograma(histograma);
    if (arbol.getRaiz() == nullptr && !histograma.empty()) { 
         std::cout << "El archivo "<< archivohuff <<" no ha podido ser abierto para decodificar."<< std::endl;
         archivo.close();
         return;
    }


    std::vector<unsigned char> bytesCodificados(
        (std::istreambuf_iterator<char>(archivo)),
         std::istreambuf_iterator<char>()
    );
    archivo.close();

    std::string cadenaBits;
    cadenaBits.reserve(cantidadBits);
    int bitsLeidos = 0;

    for (unsigned char byte : bytesCodificados) { 
        for (int j = 7; j >= 0 && bitsLeidos < cantidadBits; --j) {
            cadenaBits += ((byte >> j) & 1) ? '1' : '0';
            bitsLeidos++;
        }
        if (bitsLeidos >= cantidadBits) break;
    }

    std::vector<int> pixeles;
    int totalPixeles = static_cast<int>(W) * static_cast<int>(H);
    pixeles.reserve(totalPixeles);

    NodoHuffman* actual = arbol.getRaiz();

    if (actual != nullptr && actual->getIzquierdo() == nullptr && actual->getDerecho() == nullptr) {
        if (histograma.count(actual->getValor()) && histograma.at(actual->getValor()) == totalPixeles){
             for(int i=0; i < totalPixeles; ++i) {
                 pixeles.push_back(actual->getValor());
             }
        } else {
             std::cout << "El archivo "<< archivohuff <<" no ha podido ser abierto para decodificar." << std::endl;
             return;
        }

    } else if (actual != nullptr) { 
        for (char bit : cadenaBits) {
            if (bit == '0') {
                actual = actual->getIzquierdo();
            } else {
                actual = actual->getDerecho();
            }

            if (actual == nullptr) {
                std::cout << "El archivo "<< archivohuff <<" no ha podido ser abierto para decodificar." << std::endl;
                return;
            }

            if (actual->getIzquierdo() == nullptr && actual->getDerecho() == nullptr) {
                pixeles.push_back(actual->getValor());
                actual = arbol.getRaiz();

                if (pixeles.size() == totalPixeles) {
                    break;
                }
            }
        }
    } else if (totalPixeles > 0) {
         std::cout << "El archivo "<< archivohuff <<" no ha podido ser abierto para decodificar."<< std::endl;
         return;
    }


    if (pixeles.size() != totalPixeles) {
        std::cout << "El archivo "<< archivohuff <<" no ha podido ser abierto para decodificar." << totalPixeles << "." << std::endl;
        return;
    }

    std::ofstream salida(nombrepgm);
    if (!salida.is_open()) {
        std::cout << "El archivo "<< nombrepgm <<" no ha podido ser creado para escribir."<< std::endl; // Mejor mensaje
        return;
    }

    salida << "P2\n";
    salida << W << " " << H << "\n";
    salida << static_cast<int>(M) << "\n";

    int contador_linea = 0;
    for (int pixel : pixeles) {
        salida << pixel << " ";
        contador_linea++;
        if (contador_linea == W) {
             salida << "\n";
             contador_linea = 0;
        }
    }
    if (contador_linea != 0) {
        salida << "\n";
    }


    salida.close();
    std::cout << "El archivo " << archivohuff <<" ha sido decodificado exitosamente en "<< nombrepgm << "." << std::endl; // Mensaje más claro
}


void Sistema::cargar_imagen(std::string nombre, bool volumen){
    if(!volumen && this->imagenCargada){
        std::cout<<"UNa imagen ya fue cargada y esta será sobreescrita."<<std::endl;
    }
    std::ifstream archivo(nombre);
    if(!archivo.is_open()){
        std::cout<<"La imagen no ha podido ser cargada. No existe el archivo '"<<nombre<<"' o no está en el directorio actual."<<std::endl;
        if(volumen){
            this->volumenCargado = false;
        }
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

    std::vector<std::vector<int>> vec(altura, std::vector<int>(ancho)); 
    int pixel;

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < ancho; j++) {
            if (!(imagen >> pixel)) { 
                std::cout << "Error al leer píxeles. El archivo '"<<nombre<<"' no tiene suficientes valores." << std::endl;
                return;
            }
            if (pixel > m_valor) {
                std::cout << "La imagen no ha podido ser cargada. En el archivo "<<nombre<<" se encontró un valor mayor a m_valor." << std::endl;
                return;
            }
            vec[i][j] = pixel;
        }
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
    //this->imagen.imprimir();
}

void Sistema::cargar_volumen(std::string nombre, int n_im){
    if(this->volumenCargado){
        std::cout<<"Un volumen ya fue cargado y este será sobreescrito."<<std::endl;
    }
    if(n_im>99){
        std::cout<<"La proyección 2D del volumen en memoria no ha podido ser generada. El número máximo de imagenes es 99"<<std::endl;
        return;
    }
    if(n_im<1){
        std::cout<<"La proyección 2D del volumen en memoria no ha podido ser generada.. El número minimo de imagenes es 1"<<std::endl;
        return;
    }
    if(nombre.find('.')==std::string::npos){
        std::cout<<"La proyección 2D del volumen en memoria no ha podido ser generada. Falta la extension '.' del archivo"<<std::endl;
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
    volumen.setNombreBase(nombre);
}

void Sistema::info_volumen(){
    if(!this->volumenCargado){
        std::cout<<"Aun no se ha cargado un volumen."<<std::endl;
        return;
    }
    this->volumen.infoVolumen();
}

void Sistema::proyeccion2D(char direccion, std::string criterio, std::string nombreArchivo){
    if(!this->volumenCargado){
        std::cout<<"El volumen aun no ha sido cargado."<<std::endl;
        return;
    }


    int p = volumen.getCuenta();
    int n = volumen.getVolumen()[0].getAltoConstante();
    int m = volumen.getVolumen()[0].getAnchoConstante();

    std::vector<std::vector<int>> resultado;

    if(direccion=='z'){ //proy. de frente
        resultado.resize(n, std::vector<int>(m, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                std::vector<int> valores;
                for (int k = 0; k < p; k++) {
                    valores.push_back(volumen.getVolumen()[k].getImagen()[i][j]);
                }
                resultado[i][j] = aplCriterio(valores, criterio);
            }
        }
    }
    else if(direccion=='x'){ //proy. sobre columnas
        resultado.resize(n, std::vector<int>(p, 0));
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < p; k++) { 
                std::vector<int> valores;
                for (int j = 0; j < m; j++) { 
                    valores.push_back(volumen.getVolumen()[k].getImagen()[i][j]);
                }
                resultado[i][k] = aplCriterio(valores, criterio);
            }
        }
    }
    else if (direccion == 'y') { //vista desde arriba
        resultado.resize(p, std::vector<int>(m, 0)); 
    
        for (int k = 0; k < p; ++k) {  
            for (int j = 0; j < m; ++j) {  
                std::vector<int> valores;
                for (int i = 0; i < n; ++i) {  
                    valores.push_back(volumen.getVolumen()[k].getImagen()[i][j]);
                }
                resultado[k][j] = aplCriterio(valores, criterio); 
            }
        }
    }
    guardarArchivo(nombreArchivo, resultado);

}


int Sistema::aplCriterio(std::vector<int>& valores, std::string criterio){
    if (criterio == "minimo") {
        int minimo = valores[0];
        for (unsigned int i = 1; i < valores.size(); i++) {
            if (valores[i] < minimo) {
                minimo = valores[i];
            }
        }
        return minimo;
    }
    else if (criterio == "maximo") {
        int maximo = valores[0];
        for (unsigned int i = 1; i < valores.size(); i++) {
            if (valores[i] > maximo) {
                maximo = valores[i];
            }
        }
        return maximo;
    }
    else if (criterio == "promedio") {
        unsigned int suma = 0;
        for (unsigned int i = 0; i < valores.size(); i++) {
            suma += valores[i];
        }
        return suma / valores.size(); 
    }else if (criterio == "mediana") {
        std::vector<int> copia = valores;
        for (unsigned int i = 0; i < copia.size() - 1; ++i) {
            for (unsigned int j = i + 1; j < copia.size(); ++j) {
                if (copia[j] < copia[i]) {
                    int temp = copia[i];
                    copia[i] = copia[j];
                    copia[j] = temp;
                }
            }
        }
        unsigned int mitad = copia.size() / 2;
        if (copia.size() % 2 == 0) {
            return (copia[mitad - 1] + copia[mitad]) / 2;
        } else {
            return copia[mitad];
        }
    }
    return 0;
}


void Sistema::guardarArchivo(std::string nombre, std::vector<std::vector<int>>& imagen){
    std::ofstream archivo(nombre);
    if(!archivo.is_open()){
        std::cout<<"Error en el guardado de la proyección.";
        return;
    }
    int filas = imagen.size();
    int columnas = imagen[0].size();
    archivo << "P2\n" << columnas << " " << filas << "\n255\n";
    for (std::vector<std::vector<int>>::iterator itFila = imagen.begin(); itFila != imagen.end(); ++itFila) {
        std::vector<int>::iterator itPixel = itFila->begin();
        if (itPixel != itFila->end()) {
            archivo << *itPixel;
            itPixel++;
        }
        for (; itPixel != itFila->end(); ++itPixel) {
            archivo << " " << *itPixel; 
        }
        archivo << "\n";
    }
    std::cout<<"La proyeccion 2D ha sido generada en el archivo '"<<nombre<<"'"<<std::endl;
    archivo.close();
}