#include "Controladora.h"

Controladora::Controladora() { historial = Interfaz::crearHistorial(); }

Controladora::~Controladora() { if (historial) delete historial; }

void Controladora::controlInvalido() { Interfaz::mensajeFueraDeRango(); }

int Controladora::controlMenuPrincipal() { return Interfaz::menuPrincipal(*historial); }

void Controladora::principalControl0() {
	int op;
	do {
		op = controlMenuPrincipal();
		switch (op) {
			case 1: principalControl1(); break;
			case 2: principalControl2(); break;
			case 3: principalControl3(); break;
			case 4: principalControl4(); break;
			case 5: principalControl5(); break;
			case 6: principalControl6(); break;
			case 7: principalControl7(); break;
			case 8: principalControl8(); break;
			default: controlInvalido();
		}
	} while (op != 8);
}

void Controladora::principalControl1() { Interfaz::irASitioWeb(*historial); }

void Controladora::principalControl2() { sitiosControl0(); }

void Controladora::principalControl3() { Interfaz::crearNuevaPestana(*historial); }

void Controladora::principalControl4() { busquedaYFiltrosControl0(); }

void Controladora::principalControl5() { Interfaz::activarModoIncognito(*historial); }

void Controladora::principalControl6() { archivosControl0(); }

void Controladora::principalControl7() { configuracionControl0(); }

void Controladora::principalControl8() { Interfaz::mostrarMensajeFinal(); }

int Controladora::controlSubmenuSitio() { return Interfaz::submenuSitio(*historial); }


void Controladora::sitiosControl0() {
	int op;
	do {
		op = controlSubmenuSitio();
		switch (op) {
			case 1: sitiosControl1(); break;
			case 2: sitiosControl2(); break;
			case 3: sitiosControl3(); break;
			case 4: break;
			default: controlInvalido();
		}
	} while (op > 4 || op < 1);
}

void Controladora::sitiosControl1() { Interfaz::agregarMarcador(*historial); }

void Controladora::sitiosControl2() { Interfaz::agregarTag(*historial); }

void Controladora::sitiosControl3() { Interfaz::quitarTag(*historial); }

int Controladora::controlSubMenuArhivos() { return Interfaz::submenuArchivos(); }

void Controladora::archivosControl0() {
	int op;
	do {
		op = controlSubMenuArhivos();
		switch (op) {
			case 1: archivosControl1(); break;
			case 2: archivosControl2(); break;
			case 3: break;
			default: controlInvalido();
		}
	} while (op > 4 || op < 1);
}
void Controladora::archivosControl1() { Interfaz::serializar(*historial); }

void Controladora::archivosControl2() { Interfaz::deserializar(*historial); }

int Controladora::controlSubMenuBusquedaYFiltros() { return Interfaz::submenuBusquedaYFiltros(); }

void Controladora::busquedaYFiltrosControl0() {
	int op;
	do {
		op = controlSubMenuBusquedaYFiltros();
		switch (op) {
			case 1: busquedaYFiltrosControl1(); break;
			case 2: busquedaYFiltrosControl2(); break;
			case 3: busquedaYFiltrosControl3(); break;
			case 4: busquedaYFiltrosControl4(); break;
			case 5: break;
			default: controlInvalido();
		}
	} while (op > 5 || op < 1);
}

void Controladora::busquedaYFiltrosControl1() { Interfaz::buscarPorUrlTitulo(*historial); }

void Controladora::busquedaYFiltrosControl2() { Interfaz::buscarPorBookmarks(*historial); }

void Controladora::busquedaYFiltrosControl3() { Interfaz::filtrarPorUrlTitulo(*historial); }

void Controladora::busquedaYFiltrosControl4() { Interfaz::filtrarPorBookmarks(*historial); }

int Controladora::controlSubMenuConfiguracion() { return Interfaz::submenuConfiguracion(); }

void Controladora::configuracionControl0() {
	int op;
	do {
		op = controlSubMenuConfiguracion();
		switch (op) {
			case 1: configuracionControl1(); break;
			case 2: configuracionControl2(); break;
			case 3: break;
			default: controlInvalido();
		}
	} while (op > 4 || op < 1);
}
void Controladora::configuracionControl1() { Interfaz::cambiarLimiteEntradas(*historial); }

void Controladora::configuracionControl2() { Interfaz::cambiarLimiteTiempo(*historial); }