#pragma once
#include <chrono>
#include"Sitio.h"

class Limitador {
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