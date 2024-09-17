#include "Pestana.h"

Pestana::Pestana(int num) : numero(num) {
    sitios = new std::list<Sitio*>;
    iterador = sitios->begin();
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

std::string Pestana::mostrarPestana(){
    std::stringstream s;
    s << "    Pestaña #" << numero << '\n';
    if (sitios->empty())
        s << "Busque una página\n";
    else {
        s << (*iterador)->getUrl() << '\n';
        s << (*iterador)->getTitulo() << "\n\n";
    }
    return s.str();
}
