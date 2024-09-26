#pragma once
#include<vector>
#include<algorithm>
#include"Pestana.h"
#include"Configuracion.h"

class Navegador {
private:
    bool privado;
    std::list<Pestana*>* pestanas;
    std::vector<Sitio*>* sitios;
    std::list<Sitio*>* bookmarks;
    std::list<Pestana*>::iterator iterador;
    std::list<Pestana*>::iterator incognito;
    Configuracion* configuracion;

public:
    Navegador();
    Navegador(const Configuracion&);
    void inicializarNavegador();
    Navegador* navegadorFiltradoPorUrl(std::string);
    Navegador* navegadorFiltradoPorTitulo(std::string);
    Navegador* navegadorFiltradoPorTags(std::string);
    Navegador* navegadorFiltradoPorBookmark();
    ~Navegador();
    void eliminaTodo();

    void agregarPestana(Pestana& p);
    void agregarSitioAPestana(Sitio&);
    void agregarSitio(Sitio& p);
    void agregarQuitarBookmark();
    bool agregarTag(std::string&);
    bool quitarTag(std::string&);

    Sitio* buscarSitio(std::string);
    void leerSitios(std::ifstream&);
    std::string mostrarPestana();

    bool moverPestanaAnterior();
    bool moverPestanaSiguiente();
    bool moverSitioAnterior();
    bool moverSitioSiguiente();

    void cambiarModoIncognito();
    void activarModoIncognito();
    void desactivarModoIncognito();
    Sitio* getSitioActual();
    Pestana* getPestanaActual();

    bool existenPestanas();
    std::string mostrarBookmarks();
    std::string toString();

    void serializarNavegador(std::ofstream&);
    void deserializarNavegador(std::ifstream&);

    // Estas deserializaciones se realizan aquí ya que se requiere 
    // buscar los sitios en la lista de sitios leída desde el .csv
    void deserializarPestana(std::ifstream&, int);
    void deserializarBookmark(std::ifstream&, Bookmark&);
};