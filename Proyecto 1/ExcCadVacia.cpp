#include "ExcCadVacia.h"

ExcCadVacia::~ExcCadVacia(){}

const char* ExcCadVacia::what() const noexcept {
    return "Error: La cadena está vacía.";
}