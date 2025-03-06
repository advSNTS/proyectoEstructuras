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
    std::string nombreBase;
public:
    Volumen();
    void agregarImagen(Imagen imagen);
    void infoVolumen();
    int getCuenta();
    const std::vector<Imagen>& getVolumen() const;
    void setNombreBase(std::string nombre);
};

#endif