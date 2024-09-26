#pragma once
#include <iostream>
#include <fstream>

class Configuracion {
private:
    size_t limite;
    double tiempo;

public:
    Configuracion(size_t = 0, double = 0.0);
    ~Configuracion();

    size_t getLimite();
    double getTiempo();

    void setLimite(size_t);
    void setTiempo(double);

    void serializarConfiguracion(std::ofstream&);
    void deserializarConfiguracion(std::ifstream&);
};
