#ifndef SISTEMA_H
#define SISTEMA_H
#include "imagen.h"
#include "volumen.h"
#include "ArbolHuffman.h"
#include <iostream>
class Sistema
{
private:
    bool imagenCargada;
    bool volumenCargado;
    Imagen imagen;
    Volumen volumen;
    int anchoControlVolumen;
    int altoControlVolumen;
public:
    Sistema();
    void cargar_imagen(std::string nombre, bool volumen);
    void info_imagen();
    void cargar_volumen(std::string nombre, int n_im);
    void info_volumen();
    void proyeccion2D(char direccion, std::string criterio, std::string nombreArchivo);
    int aplCriterio(std::vector<int>& valores, std::string criterio);
    void guardarArchivo(std::string nombre, std::vector<std::vector<int>>& imagen);
    void codificarImagen(std::string nombre);
};

#endif