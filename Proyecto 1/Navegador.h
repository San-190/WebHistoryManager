#pragma once
#include<fstream>
#include<vector>
#include<algorithm>
#include"Pestana.h"
#include"Configuracion.h"

class Navegador {
private:
    std::list<Pestana*>* pestanas;
    std::vector<Sitio*>* sitios;
    std::list<Sitio*>* bookmarks;
    std::list<Pestana*>::iterator iterador;
    Configuracion* configuracion;

public:
    Navegador();
    Navegador(const Configuracion&);

    ~Navegador();

    void agregarPestana(const Pestana& p);

    void agregarSitioAPestana(Sitio&);

    void agregarSitio(const Sitio& p);

    void agregarQuitarBookmark();

    Sitio* buscarSitio(std::string);

    void leerSitios(std::ifstream&);

    std::string mostrarPestana();
    
    bool moverPestanaAnterior();
    bool moverPestanaSiguiente();

    bool moverSitioAnterior();
    bool moverSitioSiguiente();

    Sitio* getSitioActual();
};
