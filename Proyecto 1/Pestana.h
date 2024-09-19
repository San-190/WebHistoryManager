#pragma once
#include<list>
#include"Sitio.h"
#include<sstream>

class Pestana {
private:
    int numero;
    std::list<Sitio*>* sitios;
    std::list<Sitio*>::const_iterator iterador;

public:
    Pestana(int = 0);
    ~Pestana();

    int getNumero() const;
    void setNumero(int num) { numero = num; }

    void agregarSitio(const Sitio& sitio);
    std::string mostrarPestana();

    bool moverSitioAnterior();
    bool moverSitioSiguiente();
};