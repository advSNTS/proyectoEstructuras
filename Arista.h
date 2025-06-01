#ifndef ARISTA_H
#define ARISTA_H


class Arista
{
private:
    int destinoId;
    int costo;
public:
    Arista();
    Arista(int destinoId, int costo);
    ~Arista();
    int getDestinoId();
    int getCosto();
};

#endif