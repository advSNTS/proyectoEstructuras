#ifndef SISTEMA_H
#define SISTEMA_H
#include "imagen.h"
#include <iostream>
class Sistema
{
private:
    bool imagenCargara;
    Imagen imagen;
public:
    Sistema();
    void cargar_imagen(std::string nombre);
    void info_imagen();
};


#endif