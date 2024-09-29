#pragma once
#include <cctype>     // Para el uso de isspace
#include <Windows.h>
#include"Historial.h"
#include"ExcCadVacia.h"
#include"ExcValor.h"

class Interfaz{
public:
	// Interfaz principal
	static void mostrarMenuPrincipal();
	static void actualizarMenuPrincipal(Historial&);
	static int menuPrincipal(Historial&);
	static void mostrarMensajeFinal();

	// Submen�s de la interfaz
	static int submenuSitio(Historial&);
	static int submenuArchivos();
	static int submenuBusquedaYFiltros();
	static int submenuConfiguracion();
	
	// Navegaci�n del historial
	static Historial* crearHistorial();
	static void irASitioWeb(Historial&);
	static void mostrarSitio(Historial&);
	static void crearNuevaPestana(Historial&);

	// Bookmarks y Tags
	static void agregarMarcador(Historial&);
	static void agregarTag(Historial&);
	static void quitarTag(Historial&);

	// Modo Inc�gnito
	static void activarModoIncognito(Historial&);
	static void mostrarIncognito(Historial&);
	static void navegarIncognito(Historial&);

	// B�squeda y filtros
	static void buscarPorUrlTitulo(Historial&);
	static void buscarPorBookmarks(Historial& nav);
	static void filtrarPorUrlTitulo(Historial&);
	static void filtrarPorBookmarks(Historial&);
	static void mostrarSitiosEncontrados(Historial&);
	static void mostrarSitiosFiltrados(Historial&);
	static void navegarFiltros(Historial&);
		
	// Manejo de l�mites
	static void cambiarLimiteEntradas(Historial&);
	static void cambiarLimiteTiempo(Historial&);

	// Serializaci�n y Deserializaci�n
	static void serializar(Historial&);
	static void deserializar(Historial&);

	// Funciones auxiliares
	static std::string revisarString();
	static int revisaInt();
	static void mostrarPagina(Historial&);
	static void mensajeFueraDeRango();
};