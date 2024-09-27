#pragma once
#include <cctype>     // Para isspace
#include <Windows.h>
#include"Navegador.h"
#include"ExcCadVacia.h"
#include"ExcValor.h"

class Interfaz{
public:
	// Interfaz principal
	static void mostrarMenuPrincipal();
	static int menuPrincipal(Navegador&);
	static void mostrarMensajeFinal();

	// Submenus de la interfaz
	static int submenuSitio(Navegador&);
	static int submenuArchivos();
	static int submenuBusquedaYFiltros();
	static int submenuConfiguracion();
	
	// Navegacion del historial
	static Navegador* crearNavegador();
	static void irASitioWeb(Navegador&);
	static void mostrarSitio(Navegador&);
	static void crearNuevaPestana(Navegador&);

	// Bookmarks y Tags
	static void agregarMarcador(Navegador&);
	static void agregarTag(Navegador&);
	static void quitarTag(Navegador&);

	// Modo Incognito
	static void activarModoIncognito(Navegador&);
	static void mostrarIncognito(Navegador&);
	static void navegarIncognito(Navegador&);

	// Busqueda y filtros
	static void buscarPorUrlTitulo(Navegador&);
	static void buscarPorBookmarks(Navegador& nav);
	static void filtrarPorUrlTitulo(Navegador&);
	static void filtrarPorBookmarks(Navegador&);
	static void mostrarSitiosEncontrados(Navegador&);
	static void mostrarSitiosFiltrados(Navegador&);
	static void navegarFiltros(Navegador&);
		
	// Manejo de limites
	static void cambiarLimiteEntradas(Navegador&);
	static void cambiarLimiteTiempo(Navegador&);

	// Serializacion y Deserializacion
	static void serializar(Navegador&);
	static void deserializar(Navegador&);

	// Funciones auxiliares
	static std::string revisarString();
	static int revisaInt();
	static void mostrarPagina(Navegador&);
	static void mensajeFueraDeRango();
};