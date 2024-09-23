#include "Pestana.h"

int Pestana::numero = 1;

Pestana::Pestana() {
    incognito = false;
    sitios = new std::list<Sitio*>;
    iterador = sitios->begin();
    id = numero++;
}

Pestana::~Pestana() {
    delete sitios;
}

int Pestana::getNumero() const { return numero; }

bool Pestana::getIncognito(){
    return incognito;
}

void Pestana::setIncognito(bool in){
    incognito = in;
}

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
    s << "    Pestaña #" << id;
    if (incognito)
        s << " (Incógnita)";
    if (sitios->empty())
        s << "\nBusque una página\n\n";
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

void Pestana::serializarPestana(std::ofstream& archivo){
    archivo.write(reinterpret_cast<const char*>(&incognito), sizeof(incognito));
    archivo.write(reinterpret_cast<const char*>(&id), sizeof(id));

    size_t tam = sitios->size();
    archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));

    for (const auto& sitio : *sitios) {
        std::string url = sitio->getUrl();
        tam = url.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(url.c_str(), tam); 
    }
}