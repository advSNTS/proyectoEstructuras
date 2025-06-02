#include "Grafo.h"
#include <cmath>
#include <iostream>

Grafo::Grafo(){
    this->numNodos = 0;
}

Grafo::Grafo(int altoImagen, int anchoImagen, std::vector<std::vector<int>> pixelesImagen) {

    this->numNodos = altoImagen * anchoImagen;
    adj.resize(numNodos);

    auto coordenadaAId = [&](int x, int y) {
        return y * anchoImagen + x;
    };

    int dx[] = {0, 0, -1, 1}; 
    int dy[] = {-1, 1, 0, 0}; 

    for (int y = 0; y < altoImagen; ++y) {
        for (int x = 0; x < anchoImagen; ++x) {
            int idPixelActual = coordenadaAId(x, y);
            int colorPixelActual = pixelesImagen[y][x];

            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx >= 0 && nx < anchoImagen && ny >= 0 && ny < altoImagen) {

                    int idPixelVecino = coordenadaAId(nx, ny);
                    int colorPixelVecino = pixelesImagen[ny][nx];
                    int costo = std::abs(colorPixelActual - colorPixelVecino);

                    adj[idPixelActual].emplace_back(idPixelVecino, costo);

                    adj[idPixelVecino].emplace_back(idPixelActual, costo);
                }
            }
        }
    }
}


Grafo::~Grafo() = default;

int Grafo::getNumeroNodos(){
    return numNodos;
}

std::vector<Arista> Grafo::getVecinos(int idNodo)  {
    if (idNodo < 0 || idNodo >= numNodos) {
        static const std::vector<Arista> vectorVacio;
        return vectorVacio;
    }
    return adj[idNodo];
}


void Grafo::imprimirGrafo(){
    std::cout << "Grafo con " << numNodos << " nodos:" << std::endl;
    for (int i = 0; i < numNodos; ++i) {
        std::cout << "Nodo " << i << " (ID de píxel): ";
        if (adj[i].empty()) {
            std::cout << "No tiene vecinos." << std::endl;
        } else {
            std::cout << "Vecinos -> ";
            for (Arista arista : adj[i]) {
                std::cout << "(Destino: " << arista.getDestinoId() << ", Costo: " << arista.getCosto() << ") ";
            }
            std::cout << std::endl;
        }
    }
}