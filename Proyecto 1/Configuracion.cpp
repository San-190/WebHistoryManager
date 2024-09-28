#include "Configuracion.h"

Configuracion* Configuracion::instancia = nullptr;

Configuracion::Configuracion(size_t lim, std::chrono::seconds t) : limite(lim), tiempo(t) {}

void Configuracion::destruirSingleton(){
    if (instancia) {
        delete instancia;
        instancia = nullptr;
    }
}

Configuracion::~Configuracion() {}

Configuracion* Configuracion::getInstancia(){
    if (!instancia){
        instancia = new Configuracion(1000, std::chrono::seconds(3600));
        atexit(&destruirSingleton); // Al terminar el programa, se destruye el Singleton
    }
    return instancia;
}

size_t Configuracion::getLimite() { return limite; }

std::chrono::seconds Configuracion::getTiempo() { return tiempo; }

void Configuracion::setLimite(size_t lim) { limite = lim; }

void Configuracion::setTiempo(std::chrono::seconds t) { tiempo = t; }

void Configuracion::serializarConfiguracion(std::ofstream& archivo) {
    archivo.write(reinterpret_cast<const char*>(&limite), sizeof(limite));
    archivo.write(reinterpret_cast<const char*>(&tiempo), sizeof(tiempo));
}

void Configuracion::deserializarConfiguracion(std::ifstream& archivo) {
    archivo.read(reinterpret_cast<char*>(&limite), sizeof(limite));
    archivo.read(reinterpret_cast<char*>(&tiempo), sizeof(tiempo));
}
