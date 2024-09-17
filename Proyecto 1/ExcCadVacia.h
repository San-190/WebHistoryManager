#pragma once
#include<exception>

class ExcCadVacia : public std::exception {
public:
    virtual ~ExcCadVacia();
    const char* what() const noexcept override;
};