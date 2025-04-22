#ifndef IMAGEN_H
#define IMAGEN_H
#include <vector>
#include <iostream>
class Imagen
{
private:
    int ancho;
    int alto;
    int m_pixel;
    std::string nombreArchivo;
    std::vector<std::vector<int>> imagen;
public:
    Imagen(int ancho, int alto, int m_pixel, std::string nombreArchivo, std::vector<std::vector<int>> imagen);
    Imagen();
    void imprimir();
    void mostrar();
    int getAlto();
    int getAncho();
    int getMpixel();
    int getAltoConstante() const;
    int getAnchoConstante() const;
    const std::vector<std::vector<int>>& getImagen() const;
};
#endif