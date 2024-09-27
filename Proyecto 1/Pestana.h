#pragma once
#include<list>
#include"Sitio.h"
#include"Configuracion.h"
#include "Limitador.h"

class Pestana {
private:
    int id;
    std::list<Limitador*>* sitios;
    std::list<Limitador*>::const_iterator iterador;
public:
    static int numero;
    Pestana();
    ~Pestana();

    int getId();
    void setId(int);
    std::list<Limitador*>* getSitios();
    void agregarSitio(Sitio&);
    void actualizaTamano(size_t);
    std::string mostrarPestana();
    Sitio* getSitioActual();

    bool moverSitioAnterior();
    bool moverSitioSiguiente();

    void serializarPestana(std::ofstream&);
    bool quitarSitiosExpirados();
};