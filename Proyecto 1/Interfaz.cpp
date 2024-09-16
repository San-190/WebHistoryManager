#include "Interfaz.h"

int Interfaz::menuPrincipal() {
	int opcion;
	system("cls");
	std::cout << "--------- NAVEGAROAR ---------" << "\n\n";
	std::cout << "1) Ir a sitio web" << '\n';
	std::cout << "2) Agregar marcador" << '\n';
	std::cout << "3) Nueva pestaña" << '\n';
	std::cout << "4) Búsqueda y filtros" << '\n';
	std::cout << "5) Navegación privada" << '\n';
	std::cout << "6) Importar/Exportar" << '\n';
	std::cout << "7) Configuración de políticas" << '\n';
	std::cout << "8) Salir" << "\n\n";
	std::cout << "Digite la opción: ";
	std::cin >> opcion;
	return opcion;
}

Navegador* Interfaz::crearNavegador() {
	return new Navegador(*new Configuracion(0,0));
}