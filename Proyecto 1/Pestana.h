#pragma once
#include<list>
#include<fstream>
#include"Sitio.h"

class Pestana {
private:
    bool incognito;
    int id;
    std::list<Sitio*>* sitios;
    std::list<Sitio*>::const_iterator iterador;

public:
    static int numero;

    Pestana();
    ~Pestana();

    int getNumero();
    void setNumero(int);
    bool getIncognito();
    void setIncognito(bool);
    std::list<Sitio*>* getSitios();
    void agregarSitio(Sitio& sitio);
    std::string mostrarPestana();
    Sitio* getSitioActual();

    bool moverSitioAnterior();
    bool moverSitioSiguiente();

    void serializarPestana(std::ofstream&);
};