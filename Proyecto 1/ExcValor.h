#pragma once
#include <exception>
#include <string>

class ExcValor : public std::exception {
private:
    mutable std::string mensaje;
public:
    ExcValor(const std::string&);
    virtual ~ExcValor();
    virtual const char* what() const noexcept override;
};