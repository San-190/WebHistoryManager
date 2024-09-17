#pragma once
#include <algorithm>  // Para std::all_of
#include <cctype>     // Para isspace
#include"Navegador.h"
#include"ExcCadVacia.h"
#include"ExcValor.h"

class Interfaz{
public:
	static int menuPrincipal();
	static Navegador* crearNavegador();
	static void irASitioWeb(Navegador&);
	static std::string revisarString();
	static int revisaInt();
};