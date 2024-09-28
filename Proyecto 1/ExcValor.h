#pragma once
#include <exception>
#include <string>

class ExcValor : public std::exception {
private:
    mutable std::string mensaje;
    // mutable perimte que puede "mensaje" pueda modificarse dentro de una función constante
public:
    ExcValor(const std::string&);
    virtual ~ExcValor();
    virtual const char* what() const noexcept override;
    // noexcept no permite que se lancen excepciones desde aquí
};

/*
Recursos utilizados

Uso de mutable para modificar atributos en funciones constantes:
https://learn.microsoft.com/en-us/cpp/cpp/mutable-data-members-cpp?view=msvc-170
*/