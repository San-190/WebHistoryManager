#pragma once
#include"Interfaz.h"

class Controladora {
private:
	Navegador* navegador;
public:
	Controladora();
	virtual ~Controladora();
	void controlInvalido();

	int controlMenuPrincipal();
	void principalControl0();
	void principalControl1();
	void principalControl2();
	void principalControl3();
	void principalControl4();
	void principalControl5();
	void principalControl6();
	void principalControl7();
	void principalControl8();
	int controlSubmenuSitio();
	void sitiosControl0();
	void sitiosControl1();
	void sitiosControl2();
	void sitiosControl3();

};