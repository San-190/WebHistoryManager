#include "ExcValor.h"

ExcValor::ExcValor(const std::string& men):mensaje(men){}

ExcValor::~ExcValor(){}

const char* ExcValor::what() const noexcept {
    std::string s = "\n ---> " + mensaje + ". El valor ingresado es invalido.\n" +
        " No se permiten caracteres ni cantidades demasiado grandes.\n" +
        " Por favor, intentelo de nuevo\n";
    mensaje = s;
    return mensaje.c_str();
}