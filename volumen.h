#ifndef VOLUMEN_H
#define VOLUMEN_H
#include "imagen.h"
#include <vector>
#include <iostream>
class Volumen
{
private:
    std::vector<Imagen> volumen;
    int cuenta;
public:
    Volumen();
    void agregarImagen(Imagen imagen);

};

#endif