#include "Controladora.h"

Controladora::Controladora() { navegador = Interfaz::crearNavegador(); }

Controladora::~Controladora() { if (navegador) delete navegador; }

void Controladora::controlInvalido(){}

int Controladora::controlMenuPrincipal() { return Interfaz::menuPrincipal(); }

void Controladora::principalControl0() {
	int op;
	do {
		op = controlMenuPrincipal();
		system("cls");
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

void Controladora::principalControl1() {}
void Controladora::principalControl2() {}
void Controladora::principalControl3() {}
void Controladora::principalControl4() {}
void Controladora::principalControl5() {}
void Controladora::principalControl6() {}
void Controladora::principalControl7() {}
void Controladora::principalControl8() {}
