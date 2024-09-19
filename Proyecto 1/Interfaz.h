#pragma once
#include <algorithm>  // Para std::all_of
#include <cctype>     // Para isspace
#include <Windows.h>
#include"Navegador.h"
#include"ExcCadVacia.h"
#include"ExcValor.h"

class Interfaz{
public:
	static void mostrarMenuPrincipal();
	static int menuPrincipal(Navegador&);
	static int submenuSitio(Navegador&);
	static Navegador* crearNavegador();
	static void irASitioWeb(Navegador&);
	static void agregarMarcador(Navegador&);
	static void crearNuevaPestana(Navegador&);
	static void cambiarModoIncognito(Navegador&);
	static std::string revisarString();
	static int revisaInt();
	static void mostrarPagina(Navegador&);
	static void mensajeFueraDeRango();
	static void serializar(Navegador& nav);
	static void deserializar(Navegador& nav);
};