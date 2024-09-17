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
	opcion = revisaInt();
	return opcion;
}

Navegador* Interfaz::crearNavegador() {
	Navegador* nav = new Navegador();
	std::ifstream archivo("Sitios Web.csv");
	if (!archivo.fail()) {
		nav->leerSitios(archivo);
		archivo.close();
	}
	return nav;
}

void Interfaz::irASitioWeb(Navegador& nav) {
	std::string url;
	std::cout << "Escriba el url de la página: ";
	url = revisarString();
	Sitio* sitio = nav.buscarSitio(url);
	if (sitio)
		std::cout << sitio->getTitulo();
	else
		std::cout << "Error 404";
	system("pause");
}


std::string Interfaz::revisarString() {
	std::string texto;
	bool valido = false;

	while (!valido) {
		try {
			std::getline(std::cin, texto);
			// Usamos std::all_of para comprobar si todos los caracteres son espacios
			if (texto.empty() || std::all_of(texto.begin(), texto.end(), isspace)) {
				throw ExcCadVacia();
			}
			valido = true; 
		}
		catch (const ExcCadVacia& e) {
			std::cout << e.what() << '\n';
		}
		catch (...) {
			std::cout << " ---> Error desconocido\n\n";
		}
	}
	return texto;
}

int Interfaz::revisaInt() {
	int num;
	bool valido = false;

	while (!valido) {
		try {
			if (std::cin >> num && std::cin.peek() == '\n') {
				valido = true;
				std::cin.clear();
				std::cin.ignore(255, '\n');
			}
			else
				throw ExcValor("Se esperaba un numero entero");
		}
		catch (ExcValor e) {
			std::cin.clear();
			std::cin.ignore(255, '\n');
			std::cout << e.what() << '\n';
		}
		catch (...) {
			std::cout << " ---> Error desconocido\n\n";
		}
	}
	return num;
}
/*
Recursos utilizados

Funcionamiento función isspace():
https://www.tutorialspoint.com/isspace-function-in-cplusplus

Definición de all_off:
https://en.cppreference.com/w/cpp/algorithm/all_any_none_of
*/
