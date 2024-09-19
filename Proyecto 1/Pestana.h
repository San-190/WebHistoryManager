#pragma once
#include<list>
#include"Sitio.h"


class Pestana {
private:
    static int numero;
    int id;
    std::list<Sitio*>* sitios;
    std::list<Sitio*>::const_iterator iterador;

public:
    Pestana();
    ~Pestana();

    int getNumero() const;
    void setNumero(int num) { numero = num; }

    void agregarSitio(const Sitio& sitio);
    std::string mostrarPestana();
    Sitio* getSitioActual();

    bool moverSitioAnterior();
    bool moverSitioSiguiente();
};