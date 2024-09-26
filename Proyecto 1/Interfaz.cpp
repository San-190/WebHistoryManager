#include "Interfaz.h"

void Interfaz::mostrarMenuPrincipal() {
	std::cout << "--------- NAVEGAROAR ---------\n\n";
	std::cout << "1) Ir a sitio web\n";
	std::cout << "2) Opciones del sitio\n";
	std::cout << "3) Añadir nueva pestaña\n";
	std::cout << "4) Búsqueda de sitios y filtros\n";
	std::cout << "5) Activar/Desactivar Modo Incógnito\n";
	std::cout << "6) Importar/Exportar sesiones\n";
	std::cout << "7) Configuración de políticas\n";
	std::cout << "8) Salir\n\n";
	std::cout << "Digite la opción: ";
}

void Interfaz::mostrarMensajeFinal() {
	std::cout << "\n\nCerrando el NAVEGAROAR\n\n";
}

void Interfaz::mostrarSitio(Navegador& nav){
	Sitio* sitio = nav.getSitioActual();
	Bookmark* book;
	if (sitio) {
		std::cout << "Estas en el sitio: " << sitio->getUrl() << '\n';
		book = sitio->getBookmark();
		if (book)
			std::cout << book->toString() << "\n\n";
	}
}

int Interfaz::menuPrincipal(Navegador& nav) {
	system("cls");
	mostrarPagina(nav);
	mostrarMenuPrincipal();
	while (true) {
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			if (!nav.moverPestanaSiguiente()) {
				std::cout << "\nNo hay pestañas siguientes\n\n";
				system("pause");
			}
			system("cls");
			mostrarPagina(nav);
			mostrarMenuPrincipal();
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if (!nav.moverPestanaAnterior()) {
				std::cout << "\nNo hay pestañas anteriores\n\n";
				system("pause");
			}
			system("cls");
			mostrarPagina(nav);
			mostrarMenuPrincipal();
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			if (!nav.moverSitioAnterior()) {
				std::cout << "\nNo hay sitios anteriores\n\n";
				system("pause");
			}
			system("cls");
			mostrarPagina(nav);
			mostrarMenuPrincipal();
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			if (!nav.moverSitioSiguiente()) {
				std::cout << "\nNo hay sitios siguientes\n\n";
				system("pause");
			}
			system("cls");
			mostrarPagina(nav);
			mostrarMenuPrincipal();
			Sleep(200);
		}

		Sleep(100); // Retraso para evitar múltiples entradas rápidas 

		if (GetAsyncKeyState(0x31) & 0x8000)
			return 1;
		if (GetAsyncKeyState(0x32) & 0x8000)
			return 2;
		if (GetAsyncKeyState(0x33) & 0x8000)
			return 3;
		if (GetAsyncKeyState(0x34) & 0x8000)
			return 4;
		if (GetAsyncKeyState(0x35) & 0x8000)
			return 5;
		if (GetAsyncKeyState(0x36) & 0x8000)
			return 6;
		if (GetAsyncKeyState(0x37) & 0x8000)
			return 7;
		if (GetAsyncKeyState(0x38) & 0x8000)
			return 8;
	}
}

int Interfaz::submenuSitio(Navegador& nav) {
	if (!nav.getSitioActual()){
		std::cout << "\n\nDebe ingresar a un sitio para editar.\n\n";
		system("pause");
		return 4;
	}
	else {
		Pestana* pestana = nav.getPestanaActual();
		if (pestana->getIncognito()) {
			std::cout << "\n\nNo puede editar un sitio desde una pestaña incógnita.\n\n";
			system("pause");
			return 4;
		}
		else {
			system("cls");
			mostrarSitio(nav);
			std::cout << "--------- NAVEGAROAR ---------\n\n";
			std::cout << "1) Agregar / Quitar bookmark\n";
			std::cout << "2) Agregar Tag\n";
			std::cout << "3) Eliminar Tag\n";
			std::cout << "4) Volver\n\n";
			std::cout << "Digite la opción: ";
			return revisaInt();
		}
	}
}

Navegador* Interfaz::crearNavegador() {
	Navegador* nav = new Navegador();
	nav->inicializarNavegador();
	std::ifstream archivo("Sitios Web.csv");
	if (!archivo.fail()) {
		nav->leerSitios(archivo);
		archivo.close();
	}
	return nav;
}

void Interfaz::irASitioWeb(Navegador& nav) {
	std::string url;
	std::cout << "\n\nEscriba el url de la página: ";
	url = revisarString();
	Sitio* sitio = nav.buscarSitio(url);
	if (sitio)
		nav.agregarSitioAPestana(*sitio);
	else {
		std::cout << "\n404 – Not Found\n\n";
		system("pause");
	}
}

void Interfaz::agregarMarcador(Navegador& nav) {
	nav.agregarQuitarBookmark();
}

void Interfaz::agregarTag(Navegador& nav) {
	Sitio* s = nav.getSitioActual();
	std::string tag;
	if (s && s->getBookmark()) {
		std::cout << "Ingrese el tag: ";
		tag = revisarString();
		if (!nav.agregarTag(tag)) {
			std::cout << "El tag ya existe\n\n";
			system("pause");
		}
	}
	else {
		std::cout << "No se puede agregar tag porque no se encuentra en un sitio favorito\n\n";
		system("pause");
	}
}

void Interfaz::quitarTag(Navegador& nav)
{
	Sitio* s = nav.getSitioActual();
	std::string tag;
	if (s && s->getBookmark()) {
		std::cout << "Ingrese el tag que desea eliminar: ";
		tag = revisarString();
		if (!nav.quitarTag(tag)) {
			std::cout << "El tag no existe\n\n";
			system("pause");
		}
	}
	else {
		std::cout << "No se puede agregar tag porque no se encuentra en un sitio favorito\n\n";
		system("pause");
	}
}

void Interfaz::crearNuevaPestana(Navegador& nav) {
	nav.agregarPestana(*(new Pestana));
}

void Interfaz::cambiarModoIncognito(Navegador& nav) {
	nav.cambiarModoIncognito();
}


std::string Interfaz::revisarString() {
	std::string texto;
	bool valido = false;

	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
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
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

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
void Interfaz::mostrarPagina(Navegador& nav) {
	std::cout << nav.mostrarPestana();
}
void Interfaz::mensajeFueraDeRango() {
	std::cout << "\nLa opción digitada está fuera de rango\n\n";
	system("pause");
}
void Interfaz::serializar(Navegador& nav) {
	std::cout << "Ingrese el nombre de la sesión a guardar (sin extensión): ";
	std::string nombre = revisarString();
	std::ofstream archivo(nombre + ".dat", std::ios::binary);

	if (archivo.fail())
		std::cout << "No se puede abrir el archivo\n\n";
	else {
		nav.serializarNavegador(archivo);
		archivo.close();
		std::cout << "Sesión " << nombre << " guardada correctamente.\n\n";
		system("pause");
	}
}

int Interfaz::submenuArchivos() {
	system("cls");
	std::cout << "--------- NAVEGAROAR ---------\n\n";
	std::cout << "1) Guardar la sesión\n";
	std::cout << "2) Cargar la sesión\n";
	std::cout << "3) Volver\n\n";
	std::cout << "Digite la opción: ";
	return revisaInt();
}

int Interfaz::submenuBusquedaYFiltros() {
	system("cls");
	std::cout << "--------- NAVEGAROAR ---------\n\n";
	std::cout << "1) Búsqueda por URL\n";
	std::cout << "2) Búsqueda por título\n";
	std::cout << "3) Búsqueda por tag\n";
	std::cout << "4) Ver bookmarks\n";
	std::cout << "5) Filtrar por URL\n";
	std::cout << "6) Filtrar por título\n";
	std::cout << "7) Filtrar por tag\n";
	std::cout << "8) Filtrar por bookmarks\n";
	std::cout << "9) Volver\n\n";
	std::cout << "Digite la opción: ";
	return revisaInt();
}

void Interfaz::deserializar(Navegador& nav) {
	int i = 0;
	std::cout << "¿Seguro que desea cambiar de sesión? Se perderá la sesión actual.\n";
	std::cout << "Digite (1) para confirmar o (2) para cancelar.\n";
	do {
		i = revisaInt();
		if (i != 1 && i != 2)
			std::cout << "---> La opción debe ser 1 o 2.\n";
	} while (i != 1 && i != 2);

	if (i == 1) {
		std::cout << "Ingrese el nombre de la sesión a cargar (sin extensión): ";
		std::string nombre = revisarString();
		std::ifstream archivo(nombre + ".dat", std::ios::binary);

		if (archivo.fail()) {
			std::cout << "No se ha encontrado la sesión\n\n";
			system("pause");
		}
		else {
			nav.deserializarNavegador(archivo);
			archivo.close();
			std::cout << "Sesión cargada correctamente.\n\n";
		}
	}
}

void Interfaz::verBookmarks(Navegador& nav) {
	system("cls");
	std::cout << "--------- BOOKMARKS ---------\n";
	std::cout << nav.mostrarBookmarks() << '\n';
	system("pause");
}

void Interfaz::filtrarPorUrl(Navegador& nav) {
	std::string url;
	std::cout << "\n\nEscriba el filtro para los URLs: ";
	url = revisarString();
	Navegador* filtrado = nav.navegadorFiltradoPorUrl(url);
	navegarFiltros(*filtrado);
	delete filtrado;
}

int Interfaz::navegarFiltros(Navegador& nav) {
	system("cls");
	mostrarPagina(nav);
	while (true) {
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			if (!nav.moverPestanaSiguiente()) {
				std::cout << "\nNo hay pestañas siguientes\n\n";
				system("pause");
			}
			system("cls");
			mostrarPagina(nav);
			std::cout << "\n\nPresione ESC para quitar el filtro\n\n";
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if (!nav.moverPestanaAnterior()) {
				std::cout << "\nNo hay pestañas anteriores\n\n";
				system("pause");
			}
			system("cls");
			mostrarPagina(nav);
			std::cout << "\n\nPresione ESC para quitar el filtro\n\n";
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			if (!nav.moverSitioAnterior()) {
				std::cout << "\nNo hay sitios anteriores\n\n";
				system("pause");
			}
			system("cls");
			mostrarPagina(nav);
			std::cout << "\n\nPresione ESC para quitar el filtro\n\n";
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			if (!nav.moverSitioSiguiente()) {
				std::cout << "\nNo hay sitios siguientes\n\n";
				system("pause");
			}
			system("cls");
			mostrarPagina(nav);
			std::cout << "\n\nPresione ESC para quitar el filtro\n\n";
			Sleep(200);
		}

		Sleep(100); // Retraso para evitar múltiples entradas rápidas 

		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			return 9;
	}
}

/*
Recursos utilizados

Funcionamiento función isspace():
https://www.tutorialspoint.com/isspace-function-in-cplusplus

Definición de all_off:
https://en.cppreference.com/w/cpp/algorithm/all_any_none_of

Función para detectar entradas del teclado en tiempo real.
https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate#example

 Documentación de AmiBroker sobre GetAsyncKeyState (Codigos de teclas virtuales)
https://www.amibroker.com/guide/afl/getasynckeystate.html

*/