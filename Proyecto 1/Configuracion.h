#pragma once
#include <iostream>
//Si
class Configuracion {
private:
    size_t limite;
    double tiempo;

public:
    Configuracion(size_t = 0, double = 0.0);
    ~Configuracion();

    size_t getLimite() const;
    double getTiempo() const;

    void setLimite(size_t);
    void setTiempo(double);
};
