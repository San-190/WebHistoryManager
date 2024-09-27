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

	int controlSubMenuArhivos();
	void archivosControl0();
	void archivosControl1();
	void archivosControl2();

	int controlSubMenuBusquedaYFiltros();
	void busquedaYFiltrosControl0();
	void busquedaYFiltrosControl1();
	void busquedaYFiltrosControl2();
	void busquedaYFiltrosControl3();
	void busquedaYFiltrosControl4();

	int controlSubMenuConfiguracion();
	void configuracionControl0();
	void configuracionControl1();
	void configuracionControl2();
};