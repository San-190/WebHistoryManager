#include "Pestana.h"

int Pestana::numero = 1;

Pestana::Pestana() {
    sitios = new std::list<Sitio*>;
    iterador = sitios->begin();
    id = numero++;
}

Pestana::~Pestana() {
    delete sitios;
}

int Pestana::getNumero() const { return numero; }

void Pestana::agregarSitio(const Sitio& sitio) {
    if (sitios->empty()) {
        sitios->push_back((Sitio*)&sitio);
        iterador = sitios->begin();
    }
    else {
        if((*iterador)->getUrl() != sitio.getUrl()){
            sitios->push_back((Sitio*)&sitio);
            iterador = --sitios->end();
        }
    }
}

std::string Pestana::mostrarPestana(){
    std::stringstream s;
    s << "    Pestaña #" << id << '\n';
    if (sitios->empty())
        s << "Busque una página\n\n";
    else {
        s << (*iterador)->toString();
    }
    return s.str();
}

Sitio* Pestana::getSitioActual(){
    if(!sitios->empty())
        return *iterador;
    return nullptr;
}

bool Pestana::moverSitioAnterior(){
    if (sitios->empty())
        return false;
    if (iterador != sitios->begin()) {
        iterador--;
        return true;
    }
    else
        return false;
}

bool Pestana::moverSitioSiguiente(){
    if (sitios->empty())
        return false;

    iterador++;
    if (iterador != sitios->end()) {
        return true;
    }
    else{
        iterador--;
        return false;
    }
}