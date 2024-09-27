#pragma once
#include <fstream>
#include <chrono>

class Configuracion {
private:
    size_t limite;
    std::chrono::seconds tiempo;
    static Configuracion* instancia;

    Configuracion(size_t, std::chrono::seconds);
    static void destruirSingleton();
public:
    ~Configuracion();
    static Configuracion* getInstancia();

    size_t getLimite();
    std::chrono::seconds getTiempo();

    void setLimite(size_t);
    void setTiempo(std::chrono::seconds);

    void serializarConfiguracion(std::ofstream&);
    void deserializarConfiguracion(std::ifstream&);
};