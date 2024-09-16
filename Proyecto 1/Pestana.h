#pragma once
#include<list>
#include"Sitio.h"

class Pestana {
private:
    int numero;
    std::list<Sitio*>* sitios;

public:
    Pestana(int = 0);
    ~Pestana();

    int getNumero() const;
    void setNumero(int num) { numero = num; }

    void agregarSitio(const Sitio& sitio);
};