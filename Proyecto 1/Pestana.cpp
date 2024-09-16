#include "Pestana.h"

Pestana::Pestana(int num) : numero(num) {
    sitios = new std::list<Sitio*>;
}

Pestana::~Pestana() {
    for (auto p : *sitios) {
        delete p;
    }
    delete sitios;
}

int Pestana::getNumero() const { return numero; }

void Pestana::agregarSitio(const Sitio& sitio) {
    sitios->push_back((Sitio*)&sitio);
}