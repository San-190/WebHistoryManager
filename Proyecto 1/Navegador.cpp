#include "Navegador.h"

Navegador::Navegador(const Configuracion& conf) : configuracion((Configuracion*)& conf) {
    pestanas = new std::list<Pestana*>;
    sitios = new std::list<Sitio*>;
    bookmarks = new std::list<Sitio*>;
}

Navegador::~Navegador() {
    for (auto p : *pestanas) {
        delete p;
    }
    delete pestanas;

    for (auto p : *sitios) {
        delete p;
    }
    delete sitios;

    for (auto p : *bookmarks) {
        delete p;
    }
    delete bookmarks;
}

void Navegador::agregarPestana(const Pestana& p) {
    pestanas->push_back((Pestana*)&p);
}

void Navegador::agregarSitio(const Sitio& p) {
    sitios->push_back((Sitio*)&p);
}

void Navegador::agregarBookmark(const Sitio& p) {
    bookmarks->push_back((Sitio*)&p);
}