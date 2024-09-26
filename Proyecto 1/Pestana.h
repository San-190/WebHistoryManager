#pragma once
#include<list>
#include"Sitio.h"
#include"Configuracion.h"
#include "Limitador.h"

class Pestana {
private:
    bool incognito;
    int id;
    std::list<Limitador*>* sitios;
    std::list<Limitador*>::const_iterator iterador;
public:
    static int numero;

    Pestana();
    ~Pestana();

    int getNumero();
    void setNumero(int);
    bool getIncognito();
    void setIncognito(bool);
    std::list<Limitador*>* getSitios();
    void agregarSitio(Limitador&);
    void actualizaTamano(size_t);
    std::string mostrarPestana();
    Sitio* getSitioActual();

    bool moverSitioAnterior();
    bool moverSitioSiguiente();

    void serializarPestana(std::ofstream&);
    void quitarSitiosExpirados();
};