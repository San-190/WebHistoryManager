#pragma once
#include <chrono>
#include"Sitio.h"

class Limitador { // El Limitador "envuelve" un Sitio "agregándole" un timer
private:
    Sitio* sitio;
    std::chrono::time_point<std::chrono::steady_clock> tiempoInicio;

public:
    Limitador(Sitio&);
    ~Limitador();
    Sitio* getSitio();
    std::chrono::time_point<std::chrono::steady_clock> getTiempoInicio();
    void setSitio(Sitio&);
    void setTiempoInicio(std::chrono::time_point<std::chrono::steady_clock>);
};