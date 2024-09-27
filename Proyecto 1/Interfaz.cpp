#include "Interfaz.h"

void Interfaz::mostrarMenuPrincipal() {
	std::cout << "--------- TIGRESTORIAL ---------\n\n";
	std::cout << "1) Ir a sitio web\n";
	std::cout << "2) Opciones del sitio\n";
	std::cout << "3) A�adir nueva pesta�a\n";
	std::cout << "4) B�squeda y filtros\n";
	std::cout << "5) Activar Modo Inc�gnito\n";
	std::cout << "6) Importar/Exportar sesiones\n";
	std::cout << "7) Configuraci�n de pol�ticas\n";
	std::cout << "8) Salir\n\n";
	std::cout << "Digite la opci�n: ";
}

int Interfaz::menuPrincipal(Navegador& nav) {
	system("cls");
	mostrarPagina(nav);
	mostrarMenuPrincipal();
	while (true) {
		if (nav.verificaExpiraciones()) {
			system("cls");
			mostrarPagina(nav);
			mostrarMenuPrincipal();
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			if (!nav.moverPestanaSiguiente()) {
				std::cout << "\nNo hay pesta�as siguientes\n\n";
				system("pause");
			}
			system("cls");
			mostrarPagina(nav);
			mostrarMenuPrincipal();
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if (!nav.moverPestanaAnterior()) {
				std::cout << "\nNo hay pesta�as anteriores\n\n";
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

		Sleep(100); // Retraso para evitar m�ltiples entradas r�pidas 

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

void Interfaz::mostrarMensajeFinal() {
	std::cout << "\n\nCerrando el TIGRESTORIAL\n\n";
}

int Interfaz::submenuSitio(Navegador& nav) {
	if (!nav.getSitioActual()) {
		std::cout << "\n\nDebe ingresar a un sitio para editar.\n\n";
		system("pause");
		return 4;
	}
	system("cls");
	mostrarSitio(nav);
	std::cout << "--------- TIGRESTORIAL ---------\n\n";
	std::cout << "1) Agregar / Quitar bookmark\n";
	std::cout << "2) Agregar Tag\n";
	std::cout << "3) Eliminar Tag\n";
	std::cout << "4) Volver\n\n";
	std::cout << "Digite la opci�n: ";
	return revisaInt();
}

int Interfaz::submenuArchivos() {
	system("cls");
	std::cout << "--------- TIGRESTORIAL ---------\n\n";
	std::cout << "1) Guardar la sesi�n\n";
	std::cout << "2) Cargar la sesi�n\n";
	std::cout << "3) Volver\n\n";
	std::cout << "Digite la opci�n: ";
	return revisaInt();
}

int Interfaz::submenuBusquedaYFiltros() {
	system("cls");
	std::cout << "--------- TIGRESTORIAL ---------\n\n";
	std::cout << "1) B�squeda por URL/T�tulo\n";
	std::cout << "2) B�squeda por bookmarks\n";
	std::cout << "3) Filtrar por URL/T�tulo\n";
	std::cout << "4) Filtrar por bookmarks\n";
	std::cout << "5) Volver\n\n";
	std::cout << "Digite la opci�n: ";
	return revisaInt();
}

int Interfaz::submenuConfiguracion() {
	Configuracion* config = Configuracion::getInstancia();
	system("cls");
	std::cout << "--------- TIGRESTORIAL ---------\n\n";
	std::cout << "Configuraci�n actual:\n";
	std::cout << "L�mite de entradas: " << config->getLimite() << '\n';
	std::chrono::seconds segs = config->getTiempo();
	std::cout << "L�mite de tiempo: " << segs.count() << " segundos\n\n";

	std::cout << "1) Cambiar l�mite de entradas \n";
	std::cout << "2) Cambiar l�mite de tiempo\n";
	std::cout << "3) Volver\n\n";
	std::cout << "Digite la opci�n: ";
	return revisaInt();
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
	std::cout << "\n\nEscriba el url de la p�gina: ";
	url = revisarString();
	Sitio* sitio = nav.buscarSitio(url);
	if (sitio)
		nav.agregarSitioAPestana(*sitio);
	else {
		std::cout << "\n404 � Not Found\n\n";
		system("pause");
	}
}

void Interfaz::mostrarSitio(Navegador& nav) {
	Sitio* sitio = nav.getSitioActual();
	Bookmark* book;
	if (sitio) {
		std::cout << "Estas en el sitio: " << sitio->getUrl() << '\n';
		book = sitio->getBookmark();
		if (book)
			std::cout << book->toString() << "\n\n";
	}
}

void Interfaz::crearNuevaPestana(Navegador& nav) {
	nav.agregarPestana(*(new Pestana));
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

void Interfaz::quitarTag(Navegador& nav){
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

void Interfaz::activarModoIncognito(Navegador& nav) {
	Navegador* incognito = new Navegador(); // Se crea un navegador 'Auxiliar' para la navegaci�n inc�gnita
	Configuracion* config = Configuracion::getInstancia(); 
	size_t tamanio = config->getLimite();			// Guardamos los valores actuales de la configuraci�n
	std::chrono::seconds tiempo = config->getTiempo();
	int numero = Pestana::numero;	// Se guarda el n�mero de pesta�as que habian en navegaci�n normal
	Pestana::numero = 1;  // Y se resetea el contador de pesta�as para el nuevo navegador de inc�gnito
	incognito->inicializarNavegador();		
	incognito->setSitios(nav.getSitios());	// Al navegador le damos los sitios disponibles para la navegaci�n

	config->setLimite(1);		// Y se establecen las nuevas configuraciones para esta navegaci�n 
	config->setTiempo(std::chrono::seconds(999999999)); // (No hay pesta�as anteriores, y el l�mite de tiempo es muy grande)

	navegarIncognito(*incognito);  // Aqu� puede navegar buscando sitios y creando nuevas pesta�as inc�gnitas
	incognito->setSitios(nullptr); // Cuando el usuario presiona 'ESC', se desvinculan los sitios disponibles del navegador Inc�gnito para su destrucci�n
	delete incognito;

	config->setLimite(tamanio); // Y por �ltimo se regresa la configuraci�n que tenia el navegador original
	config->setTiempo(tiempo);  // junto al n�mero de pesta�as para continuar con la navegaci�n normal
	Pestana::numero = numero;
}

void Interfaz::mostrarIncognito(Navegador& nav) {
	system("cls");
	std::cout << "--------Navegador Inc�gnito--------\n\n";
	mostrarPagina(nav);
	std::cout << "1) Ir a sitio web\n";
	std::cout << "2) A�adir nueva pesta�a\n";
	std::cout << "\n---> Presione ESC para salir del modo inc�gnito\n\n";
}

void Interfaz::navegarIncognito(Navegador& nav) {
	mostrarIncognito(nav);
	while (true) {
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			if (!nav.moverPestanaSiguiente()) {
				std::cout << "\nNo hay pesta�as siguientes\n\n";
				system("pause");
			}
			mostrarIncognito(nav);
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if (!nav.moverPestanaAnterior()) {
				std::cout << "\nNo hay pesta�as anteriores\n\n";
				system("pause");
			}
			mostrarIncognito(nav);
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			if (!nav.moverSitioAnterior()) {
				std::cout << "\nNo hay sitios anteriores\n\n";
				system("pause");
			}
			mostrarIncognito(nav);
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			if (!nav.moverSitioSiguiente()) {
				std::cout << "\nNo hay sitios siguientes\n\n";
				system("pause");
			}
			mostrarIncognito(nav);
			Sleep(200);
		}
		Sleep(100); // Retraso para evitar m�ltiples entradas r�pidas 

		if (GetAsyncKeyState(0x31) & 0x8000) {
			irASitioWeb(nav);
			mostrarIncognito(nav);
		}

		if (GetAsyncKeyState(0x32) & 0x8000) {
			crearNuevaPestana(nav);
			mostrarIncognito(nav);
		}

		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			return;
	}
}

void Interfaz::buscarPorUrlTitulo(Navegador& nav) {
	std::string entrada;
	std::cout << "\n\nEscriba la entrada a buscar: ";
	entrada = revisarString();
	Navegador* filtrado = nav.navegadorFiltradoPorUrlTitulo(entrada);
	mostrarSitiosEncontrados(*filtrado);
	delete filtrado;
}

void Interfaz::buscarPorBookmarks(Navegador& nav) {
	Navegador* filtrado = nav.navegadorFiltradoPorBookmark();
	mostrarSitiosEncontrados(*filtrado);
	delete filtrado;
}

void Interfaz::filtrarPorUrlTitulo(Navegador& nav) {
	std::string filtro;
	std::cout << "\n\nEscriba el filtro: ";
	filtro = revisarString();
	Navegador* filtrado = nav.navegadorFiltradoPorUrlTitulo(filtro);
	if (filtrado->existenPestanas())
		navegarFiltros(*filtrado);
	else {
		std::cout << "\n---> No se encontraron coincidencias.\n\n";
		system("pause");
	}
	delete filtrado;
}

void Interfaz::filtrarPorBookmarks(Navegador& nav) {
	Navegador* filtrado = nav.navegadorFiltradoPorBookmark();
	if (filtrado->existenPestanas())
		navegarFiltros(*filtrado);
	else {
		std::cout << "\n---> No se encontraron coincidencias.\n\n";
		system("pause");
	}
	delete filtrado;
}

void Interfaz::mostrarSitiosEncontrados(Navegador& nav) {
	system("cls");
	std::cout << "-----Coincidencias Encontradas-----\n";
	if (nav.existenPestanas())
		std::cout << nav.toString() << '\n';
	else
		std::cout << "---> No se encontraron coincidencias.\n\n";
	system("pause");
}

void Interfaz::mostrarSitiosFiltrados(Navegador& nav) {
	system("cls");
	std::cout << "--------TIGRESTORIAL Filtrado--------\n\n";
	mostrarPagina(nav);
	std::cout << "\n---> Utilice las flechas para moverse entre pesta�as y sitios\n";
	std::cout << "---> Presione ESC para quitar el filtro\n\n";
}

void Interfaz::navegarFiltros(Navegador& nav) {
	mostrarSitiosFiltrados(nav);
	while (true) {

		if (nav.verificaExpiraciones()) {
			system("cls");
			mostrarSitiosFiltrados(nav);
		}
		
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			if (!nav.moverPestanaSiguiente()) {
				std::cout << "\nNo hay pesta�as siguientes\n\n";
				system("pause");
			}
			mostrarSitiosFiltrados(nav);
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if (!nav.moverPestanaAnterior()) {
				std::cout << "\nNo hay pesta�as anteriores\n\n";
				system("pause");
			}
			mostrarSitiosFiltrados(nav);
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			if (!nav.moverSitioAnterior()) {
				std::cout << "\nNo hay sitios anteriores\n\n";
				system("pause");
			}
			mostrarSitiosFiltrados(nav);
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			if (!nav.moverSitioSiguiente()) {
				std::cout << "\nNo hay sitios siguientes\n\n";
				system("pause");
			}
			mostrarSitiosFiltrados(nav);
			Sleep(200);
		}
		Sleep(100); // Retraso para evitar m�ltiples entradas r�pidas 

		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			return;
	}
}

void Interfaz::cambiarLimiteEntradas(Navegador& nav) {
	int lim;
	std::cout << "\n\nEscriba el nuevo l�mite: ";
	do {
		lim = revisaInt();
		if (lim < 1)
			std::cout << "---> El l�mite debe ser mayor a 0.\n";
	} while (lim < 1);
	Configuracion* config = Configuracion::getInstancia();
	config->setLimite(lim);
	nav.actualizarLimites(lim);
}

void Interfaz::cambiarLimiteTiempo(Navegador& nav) {
	int lim;
	std::cout << "\n\nEscriba el nuevo l�mite: ";
	do {
		lim = revisaInt();
		if (lim < 1)
			std::cout << "---> El l�mite debe ser mayor a 0.\n";
	} while (lim < 1);
	Configuracion* config = Configuracion::getInstancia();
	config->setTiempo(std::chrono::seconds(lim));
}

void Interfaz::serializar(Navegador& nav) {
	std::cout << "Ingrese el nombre de la sesi�n a guardar (sin extensi�n): ";
	std::string nombre = revisarString();
	std::ofstream archivo(nombre + ".dat", std::ios::binary);

	if (archivo.fail())
		std::cout << "No se puede abrir el archivo\n\n";
	else {
		nav.serializarNavegador(archivo);
		archivo.close();
		std::cout << "Sesi�n " << nombre << " guardada correctamente.\n\n";
		system("pause");
	}
}

void Interfaz::deserializar(Navegador& nav) {
	int i = 0;
	std::cout << "�Seguro que desea cambiar de sesi�n? Se perder� la sesi�n actual.\n";
	std::cout << "Digite (1) para confirmar o (2) para cancelar.\n";
	do {
		i = revisaInt();
		if (i != 1 && i != 2)
			std::cout << "---> La opci�n debe ser 1 o 2.\n";
	} while (i != 1 && i != 2);

	if (i == 1) {
		std::cout << "Ingrese el nombre de la sesi�n a cargar (sin extensi�n): ";
		std::string nombre = revisarString();
		std::ifstream archivo(nombre + ".dat", std::ios::binary);

		if (archivo.fail()) {
			std::cout << "No se ha encontrado la sesi�n\n\n";
			system("pause");
		}
		else {
			nav.deserializarNavegador(archivo);
			archivo.close();
			std::cout << "Sesi�n cargada correctamente.\n\n";
		}
	}
}
std::string Interfaz::revisarString() {
	std::string texto;
	bool valido = false;

	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); // Esta funcion limpia el buffer para que cualquier caracter
	// que haya sido escrito no se muestre al digitar una opcion valida en la navegacion.
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
	std::cout << "\nLa opci�n digitada est� fuera de rango\n\n";
	system("pause");
}
/*
Recursos utilizados

Funcionamiento funci�n isspace():
https://www.tutorialspoint.com/isspace-function-in-cplusplus

Definici�n de all_off:
https://en.cppreference.com/w/cpp/algorithm/all_any_none_of

Funci�n para detectar entradas del teclado en tiempo real.
https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate#example

 Documentaci�n de AmiBroker sobre GetAsyncKeyState (Codigos de teclas virtuales)
https://www.amibroker.com/guide/afl/getasynckeystate.html

*/