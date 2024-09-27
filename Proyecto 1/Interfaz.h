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
	static void mostrarMensajeFinal();
	static void mostrarSitio(Navegador&);
	static int menuPrincipal(Navegador&);
	static int submenuSitio(Navegador&);
	static int submenuArchivos();
	static int submenuBusquedaYFiltros();
	static int submenuConfiguracion();
	static Navegador* crearNavegador();
	static void irASitioWeb(Navegador&);
	static void agregarMarcador(Navegador&);
	static void agregarTag(Navegador&);
	static void quitarTag(Navegador&);
	static void crearNuevaPestana(Navegador&);

	static void activarModoIncognito(Navegador&);
	static void mostrarIncognito(Navegador&);
	static void navegarIncognito(Navegador&);

	static std::string revisarString();
	static int revisaInt();
	static void mostrarPagina(Navegador&);
	static void mensajeFueraDeRango();
	static void serializar(Navegador&);
	static void deserializar(Navegador&);
	static void buscarPorUrlTitulo(Navegador&);
	static void buscarPorBookmarks(Navegador& nav);
	static void filtrarPorUrlTitulo(Navegador&);
	static void filtrarPorBookmarks(Navegador&);
	static void mostrarSitiosEncontrados(Navegador&);
	static void mostrarSitiosFiltrados(Navegador&);
	static int navegarFiltros(Navegador&);
	static void cambiarLimiteEntradas(Navegador&);
	static void cambiarLimiteTiempo(Navegador&);
};