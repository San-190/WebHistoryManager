#include "Controladora.h"

Controladora::Controladora() { navegador = Interfaz::crearNavegador(); }

Controladora::~Controladora() { if (navegador) delete navegador; }

void Controladora::controlInvalido() { Interfaz::mensajeFueraDeRango(); }

int Controladora::controlMenuPrincipal() { return Interfaz::menuPrincipal(*navegador); }

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

void Controladora::principalControl1() { Interfaz::irASitioWeb(*navegador); }
void Controladora::principalControl2() { sitiosControl0(); }
void Controladora::principalControl3() { Interfaz::crearNuevaPestana(*navegador); }
void Controladora::principalControl4() {}
void Controladora::principalControl5() { Interfaz::cambiarModoIncognito(*navegador); }
void Controladora::principalControl6() { archivosControl0(); }
void Controladora::principalControl7() {}
void Controladora::principalControl8() { Interfaz::mostrarMensajeFinal(); }
int Controladora::controlSubmenuSitio() { return Interfaz::submenuSitio(*navegador); }

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
void Controladora::sitiosControl1() { Interfaz::agregarMarcador(*navegador); }
void Controladora::sitiosControl2() { Interfaz::agregarTag(*navegador); }
void Controladora::sitiosControl3() { Interfaz::quitarTag(*navegador); }
int Controladora::controlSubMenuArhivos(){ return Interfaz::menuArchivos(); }
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
void Controladora::archivosControl1() { Interfaz::serializar(*navegador); }
void Controladora::archivosControl2() { Interfaz::deserializar(*navegador); }
