#pragma once
#include<algorithm>
#include"Pestana.h"

class Navegador {
private:
    std::list<Pestana*>* pestanas;
    std::vector<Sitio*>* sitios;
    std::vector<Sitio*>* bookmarks;
    std::list<Pestana*>::iterator iterador;

public:
    Navegador();
    ~Navegador();
    void inicializarNavegador();
    Navegador* navegadorFiltradoPorUrlTitulo(std::string);
    Navegador* navegadorFiltradoPorBookmark();
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

    void setSitios(std::vector<Sitio*>*);
    std::vector<Sitio*>* getSitios();
    Sitio* getSitioActual();
    Pestana* getPestanaActual();
    void actualizarLimites(int);
    bool verificaExpiraciones();
    void verificaExpiracionesEnTodas();

    bool existenPestanas();
    std::string mostrarBookmarks();
    std::string toString();

    void serializarNavegador(std::ofstream&);
    void deserializarNavegador(std::ifstream&);

    // Estas deserializaciones se realizan aquí ya que se requiere 
    // buscar los sitios en la lista de sitios leída desde el .csv
    void deserializarPestana(std::ifstream&);
    void deserializarBookmark(std::ifstream&, Bookmark&);


};