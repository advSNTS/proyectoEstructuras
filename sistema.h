#ifndef SISTEMA_H
#define SISTEMA_H
#include "imagen.h"
#include "volumen.h"
#include <iostream>
class Sistema
{
private:
    bool imagenCargara;
    Imagen imagen;
    Volumen volumen;
public:
    Sistema();
    void cargar_imagen(std::string nombre, bool volumen);
    void info_imagen();
    void cargar_volumen(std::string nombre, int n_im);
    void info_volumen();
};


#endif