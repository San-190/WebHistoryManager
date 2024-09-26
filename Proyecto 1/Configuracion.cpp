#include "Configuracion.h"

Configuracion::Configuracion(size_t lim, double t) : limite(lim), tiempo(t) {}

Configuracion::~Configuracion(){}

size_t Configuracion::getLimite() { return limite; }

double Configuracion::getTiempo() { return tiempo; }

void Configuracion::setLimite(size_t lim) { limite = lim; }

void Configuracion::setTiempo(double t) { tiempo = t; }

void Configuracion::serializarConfiguracion(std::ofstream& archivo) {
    archivo.write(reinterpret_cast<const char*>(&limite), sizeof(limite));
    archivo.write(reinterpret_cast<const char*>(&tiempo), sizeof(tiempo));
}

void Configuracion::deserializarConfiguracion(std::ifstream& archivo) {
    archivo.read(reinterpret_cast<char*>(&limite), sizeof(limite));
    archivo.read(reinterpret_cast<char*>(&tiempo), sizeof(tiempo));
}