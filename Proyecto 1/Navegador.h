#pragma onc
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
    ~Navegador();

    void agregarPestana(Pestana& p);
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

    void cambiarModoIncognito();
    void activarModoIncognito();
    void desactivarModoIncognito();
    Sitio* getSitioActual();

    void serializarNavegador(std::ofstream&);
    void deserializarNavegador(std::ifstream&);
};
