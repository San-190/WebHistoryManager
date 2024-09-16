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
    Configuracion* configuracion;

public:
    Navegador();
    Navegador(const Configuracion&);

    ~Navegador();

    void agregarPestana(const Pestana& p);

    void agregarSitio(const Sitio& p);

    void agregarBookmark(const Sitio& p);

    Sitio* buscarSitio(std::string);

    void leerSitios(std::ifstream&);
};
