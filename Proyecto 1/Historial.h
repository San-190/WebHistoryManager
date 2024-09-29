#pragma once
#include<algorithm>
#include"Pestana.h"

class Historial {
private:
    std::list<Pestana*>* pestanas;
    std::vector<Sitio*>* sitios;
    std::vector<Sitio*>* bookmarks; // El vector de Bookmarks se utiliza para facilitar el proceso de serialización
    std::list<Pestana*>::iterator iterador;

public:
    Historial();
    ~Historial();
    void inicializarHistorial();
    Historial* historialFiltradoPorUrlTitulo(std::string);
    Historial* historialFiltradoPorBookmark();
    void reiniciar();

    void agregarPestana(Pestana& p);
    void agregarSitioAPestana(Sitio&);
    void agregarSitio(Sitio& p);
    void agregarQuitarBookmark();
    bool agregarTag(std::string&);
    bool quitarTag(std::string&);

    Sitio* buscarSitio(std::string);
    void leerSitios(std::ifstream&);
    std::string mostrarPestana();

    void moverPestanaInicial();
    bool moverPestanaAnterior();
    bool moverPestanaSiguiente();
    bool moverSitioAnterior();
    bool moverSitioSiguiente();

    void setSitios(std::vector<Sitio*>*);
    std::vector<Sitio*>* getSitios();
    Sitio* getSitioActual();
    Pestana* getPestanaActual();
    std::list<Pestana*>* getPestanas();
    void actualizarLimites(int);
    bool verificaExpiraciones();
    void verificaExpiracionesEnTodas();
    bool existenPestanas();
    std::string toString();

    void serializarHistorial(std::ofstream&);
    void deserializarHistorial(std::ifstream&);
    // Estas deserializaciones se realizan aquí ya que se requiere 
    // buscar los sitios en la lista de sitios leída desde el .csv
    void deserializarPestanas(std::ifstream&);
    void deserializarBookmark(std::ifstream&, Bookmark&);
};