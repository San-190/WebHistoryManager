#pragma once
#include<list>
#include"Configuracion.h"
#include "Limitador.h"

class Pestana {
private:
    int id;
    std::list<Limitador*>* sitios;
    std::list<Limitador*>::const_iterator iterador;
public:
    static int numero; // Número de Pestaña static para que sea accesible para todas
    Pestana();
    ~Pestana();

    int getId();
    void setId(int);
    std::list<Limitador*>* getSitios();            // Por defecto, se recibe un tiempo equivalente a 0
    void agregarSitio(Sitio&, std::chrono::time_point<std::chrono::steady_clock> = std::chrono::steady_clock::time_point());
    void actualizaTamano(size_t);
    std::string mostrarPestana();
    bool quitarSitiosExpirados();
    Sitio* getSitioActual();

    bool moverSitioAnterior();
    bool moverSitioSiguiente();
    void serializarPestana(std::ofstream&);
};