#pragma once
#include"Pestana.h"
#include"Configuracion.h"

class Navegador {
private:
    std::list<Pestana*>* pestanas;
    std::list<Sitio*>* sitios;
    std::list<Sitio*>* bookmarks;
    Configuracion* configuracion;

public:
    Navegador(const Configuracion&);

    ~Navegador();

    void agregarPestana(const Pestana& p);

    void agregarSitio(const Sitio& p);

    void agregarBookmark(const Sitio& p);
};
