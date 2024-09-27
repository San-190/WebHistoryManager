#include "Limitador.h"

Limitador::Limitador(Sitio& s) {
    sitio = (Sitio*)&s;
    tiempoInicio = std::chrono::steady_clock::now();
}

Limitador::~Limitador(){}

Sitio* Limitador::getSitio(){
    return sitio;
}

std::chrono::time_point<std::chrono::steady_clock> Limitador::getTiempoInicio(){
    return tiempoInicio;
}

void Limitador::setSitio(Sitio& s){
    sitio = (Sitio*)&s;
}

void Limitador::setTiempoInicio(std::chrono::time_point<std::chrono::steady_clock> t){
    tiempoInicio = t;
}

/*
Recursos utilizados

Uso de std::chrono::steady_clock para medir tiempo:
https://en.cppreference.com/w/cpp/chrono/steady_clock
*/