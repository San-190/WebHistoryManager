#pragma once
#include <fstream>
#include <chrono>

class Configuracion {
private:
    size_t limite; // Límite de entradas
    std::chrono::seconds tiempo; // Límite de tiempo
    static Configuracion* instancia; // Instancia (esta clase es Singleton)

    Configuracion(size_t, std::chrono::seconds);
    static void destruirSingleton();
public:
    ~Configuracion();
    static Configuracion* getInstancia();

    size_t getLimite();
    std::chrono::seconds getTiempo();

    //Metodo para reestablecer la instancia, solamente se usa para el unit testing
    static void liberarInstancia();

    void setLimite(size_t);
    void setTiempo(std::chrono::seconds);

    void serializarConfiguracion(std::ofstream&);
    void deserializarConfiguracion(std::ifstream&);
};