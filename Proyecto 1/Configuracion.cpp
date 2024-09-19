#include "Configuracion.h"

Configuracion::Configuracion(size_t lim, double t) : limite(lim), tiempo(t) {}

Configuracion::~Configuracion(){}

size_t Configuracion::getLimite() const { return limite; }

double Configuracion::getTiempo() const { return tiempo; }

void Configuracion::setLimite(size_t lim) { limite = lim; }

void Configuracion::setTiempo(double t) { tiempo = t; }

void Configuracion::serializarConfiguracion(std::ofstream& archivo) {
    archivo.write(reinterpret_cast<const char*>(&limite), sizeof(limite));
    archivo.write(reinterpret_cast<const char*>(&tiempo), sizeof(tiempo));
}