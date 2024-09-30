#include "Interfaz.h"

void Interfaz::mostrarMenuPrincipal() {
	std::cout << "--------- TIGRESTORIAL ---------\n\n";
	std::cout << "1) Ir a sitio web\n";
	std::cout << "2) Opciones del sitio\n";
	std::cout << "3) Añadir nueva pestaña\n";
	std::cout << "4) Búsqueda y filtros\n";
	std::cout << "5) Activar Modo Incógnito\n";
	std::cout << "6) Importar/Exportar sesiones\n";
	std::cout << "7) Configuración de políticas\n";
	std::cout << "8) Salir\n\n";
	std::cout << "Digite la opción: ";
}

void Interfaz::actualizarMenuPrincipal(Historial& his){
	system("cls");
	his.verificaExpiraciones();
	mostrarPagina(his);
	mostrarMenuPrincipal();
}

int Interfaz::menuPrincipal(Historial& his) {
	actualizarMenuPrincipal(his);

	while (true) { // En este ciclo, se escuchan las teclas direccionales con el objetivo de Navegar
		if (his.verificaExpiraciones()) {
			system("cls");
			mostrarPagina(his);
			mostrarMenuPrincipal();
		}

		// Flecha de arriba
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			if (!his.moverPestanaSiguiente()) {
				std::cout << "\nNo hay pestañas siguientes\n\n";
				system("pause");
			}
			actualizarMenuPrincipal(his);
			Sleep(200);
		}

		// Flecha de abajo
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if (!his.moverPestanaAnterior()) {
				std::cout << "\nNo hay pestañas anteriores\n\n";
				system("pause");
			}
			actualizarMenuPrincipal(his);
			Sleep(200);
		}

		// Flecha izquierda
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			if (!his.moverSitioAnterior()) {
				std::cout << "\nNo hay sitios anteriores\n\n";
				system("pause");
			}
			actualizarMenuPrincipal(his);
			Sleep(200);
		}

		// Flecha derecha
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			if (!his.moverSitioSiguiente()) {
				std::cout << "\nNo hay sitios siguientes\n\n";
				system("pause");
			}
			actualizarMenuPrincipal(his);
			Sleep(200);
		}

		Sleep(100); // Retraso para evitar múltiples entradas rápidas 

		// Aquí se escuchan los números correspondientes a las opciones del menú
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

int Interfaz::submenuSitio(Historial& his) {
	if (!his.getSitioActual()) {
		std::cout << "\n\nDebe ingresar a un sitio para editar.\n\n";
		system("pause");
		return 4;
	}
	system("cls");
	mostrarSitio(his);
	std::cout << "--------- TIGRESTORIAL ---------\n\n";
	std::cout << "1) Agregar / Quitar bookmark\n";
	std::cout << "2) Agregar Tag\n";
	std::cout << "3) Eliminar Tag\n";
	std::cout << "4) Volver\n\n";
	std::cout << "Digite la opción: ";
	return revisaInt();
}

int Interfaz::submenuArchivos() {
	system("cls");
	std::cout << "--------- TIGRESTORIAL ---------\n\n";
	std::cout << "1) Guardar la sesión\n";
	std::cout << "2) Cargar la sesión\n";
	std::cout << "3) Volver\n\n";
	std::cout << "Digite la opción: ";
	return revisaInt();
}

int Interfaz::submenuBusquedaYFiltros() {
	system("cls");
	std::cout << "--------- TIGRESTORIAL ---------\n\n";
	std::cout << "1) Búsqueda por URL/Título\n";
	std::cout << "2) Búsqueda por bookmarks\n";
	std::cout << "3) Filtrar por URL/Título\n";
	std::cout << "4) Filtrar por bookmarks\n";
	std::cout << "5) Volver\n\n";
	std::cout << "Digite la opción: ";
	return revisaInt();
}

int Interfaz::submenuConfiguracion() {
	Configuracion* config = Configuracion::getInstancia();
	system("cls");
	std::cout << "--------- TIGRESTORIAL ---------\n\n";
	std::cout << "Configuración actual:\n";
	std::cout << "Límite de entradas: " << config->getLimite() << '\n';
	std::chrono::seconds segs = config->getTiempo();
	// count permite imprimir los segundos como si fueran un entero
	std::cout << "Límite de tiempo: " << segs.count() << " segundos\n\n";

	std::cout << "1) Cambiar límite de entradas \n";
	std::cout << "2) Cambiar límite de tiempo\n";
	std::cout << "3) Volver\n\n";
	std::cout << "Digite la opción: ";
	return revisaInt();
}

Historial* Interfaz::crearHistorial() {
	Historial* his = nullptr;
	std::ifstream archivo("Sitios Web.csv");
	if (!archivo.fail()) {
		his = new Historial();
		his->inicializarHistorial();
		his->leerSitios(archivo);
		archivo.close();
	}
	else {
		std::cerr << "---> No se ha encontrado el archivo 'Sitios Web.csv' para cargar los sitios...\n\n";
		exit(1); // Si el programa cierra con código 1, es que no se encon´tró el archivo csv con los Sitios
	}
	return his;
}

void Interfaz::irASitioWeb(Historial& his) {
	std::string url;
	std::cout << "\n\nEscriba el url de la página: ";
	url = revisarString();
	Sitio* sitio = his.buscarSitio(url);
	if (sitio)
		his.agregarSitioAPestana(*sitio);
	else {
		std::cout << "\n404 – Not Found\n\n";
		system("pause");
	}
}

void Interfaz::mostrarSitio(Historial& his) {
	Sitio* sitio = his.getSitioActual();
	Bookmark* book;
	if (sitio) {
		std::cout << "Estas en el sitio: " << sitio->getUrl() << '\n';
		book = sitio->getBookmark();
		if (book)
			std::cout << book->toString() << "\n\n";
	}
}

void Interfaz::crearNuevaPestana(Historial& his) {
	his.agregarPestana(*(new Pestana));
}

void Interfaz::agregarMarcador(Historial& his) {
	his.agregarQuitarBookmark();
}

void Interfaz::agregarTag(Historial& his) {
	Sitio* s = his.getSitioActual();
	std::string tag;
	if (s && s->getBookmark()) {
		std::cout << "Ingrese el tag: ";
		tag = revisarString();
		if (!his.agregarTag(tag)) {
			std::cout << "El tag ya existe\n\n";
			system("pause");
		}
	}
	else {
		std::cout << "No se puede agregar tag porque no se encuentra en un sitio favorito\n\n";
		system("pause");
	}
}

void Interfaz::quitarTag(Historial& his){
	Sitio* s = his.getSitioActual();
	std::string tag;
	if (s && s->getBookmark()) {
		std::cout << "Ingrese el tag que desea eliminar: ";
		tag = revisarString();
		if (!his.quitarTag(tag)) {
			std::cout << "El tag no existe\n\n";
			system("pause");
		}
	}
	else {
		std::cout << "No se puede agregar tag porque no se encuentra en un sitio favorito\n\n";
		system("pause");
	}
}

void Interfaz::activarModoIncognito(Historial& his) {
	// Se crea un Historial auxiliar para la navegación incógnita
	Historial* incognito = new Historial();

	// Guardamos los valores actuales de la configuración, para setearlos de vuelta al terminar la navegación privada
	Configuracion* config = Configuracion::getInstancia(); 
	size_t tamanio = config->getLimite();			
	std::chrono::seconds tiempo = config->getTiempo();

	// Se guarda el número de pestañas que había en navegación normal, y se resetean para iniciar desde 1
	int numero = Pestana::numero;
	Pestana::numero = 1;

	// Al Historial le damos los sitios disponibles para la navegación
	incognito->inicializarHistorial();		
	incognito->setSitios(his.getSitios());

	// Se establecen las nuevas configuraciones para esta navegación (solo se permite un Sitio por pestaña y el límite de tiempo es muy grande)
	config->setLimite(1);		
	config->setTiempo(std::chrono::seconds(999999999));

	// Aquí comienza la navegación, buscando sitios y creando nuevas pestañas incógnitas
	navegarIncognito(*incognito);

	// Cuando el usuario presiona 'ESC', se desvinculan los sitios disponibles del Historial Incógnito para su destrucción
	incognito->setSitios(nullptr);
	delete incognito;

	// Finalmente, se vuelven a setear los valores de la configuración y número de pestañas de la navegación normal
	config->setLimite(tamanio);
	config->setTiempo(tiempo);
	Pestana::numero = numero;
}

void Interfaz::mostrarIncognito(Historial& his) {
	system("cls");
	std::cout << "--------Historial Incógnito--------\n\n";
	mostrarPagina(his);
	std::cout << "1) Ir a sitio web\n";
	std::cout << "2) Añadir nueva pestaña\n";
	std::cout << "\n---> Presione ESC para salir del modo incógnito\n\n";
}

void Interfaz::navegarIncognito(Historial& his) {
	mostrarIncognito(his);
	while (true) {
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			if (!his.moverPestanaSiguiente()) {
				std::cout << "\nNo hay pestañas siguientes\n\n";
				system("pause");
			}
			mostrarIncognito(his);
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if (!his.moverPestanaAnterior()) {
				std::cout << "\nNo hay pestañas anteriores\n\n";
				system("pause");
			}
			mostrarIncognito(his);
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			if (!his.moverSitioAnterior()) {
				std::cout << "\nNo hay sitios anteriores\n\n";
				system("pause");
			}
			mostrarIncognito(his);
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			if (!his.moverSitioSiguiente()) {
				std::cout << "\nNo hay sitios siguientes\n\n";
				system("pause");
			}
			mostrarIncognito(his);
			Sleep(200);
		}
		Sleep(100); // Retraso para evitar múltiples entradas rápidas 

		if (GetAsyncKeyState(0x31) & 0x8000) {
			irASitioWeb(his);
			mostrarIncognito(his);
		}

		if (GetAsyncKeyState(0x32) & 0x8000) {
			crearNuevaPestana(his);
			mostrarIncognito(his);
		}

		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			return;
	}
}

void Interfaz::buscarPorUrlTitulo(Historial& his) {
	std::string entrada;
	std::cout << "\n\nEscriba la entrada a buscar: ";
	entrada = revisarString();
	Historial* filtrado = his.historialFiltradoPorUrlTitulo(entrada);
	mostrarSitiosEncontrados(*filtrado);
	delete filtrado;
}

void Interfaz::buscarPorBookmarks(Historial& his) {
	Historial* filtrado = his.historialFiltradoPorBookmark();
	mostrarSitiosEncontrados(*filtrado);
	delete filtrado;
}

void Interfaz::filtrarPorUrlTitulo(Historial& his) {
	std::string filtro;
	std::cout << "\n\nEscriba el filtro: ";
	filtro = revisarString();
	Historial* filtrado = his.historialFiltradoPorUrlTitulo(filtro);
	if (filtrado->existenPestanas())
		navegarFiltros(*filtrado);
	else {
		std::cout << "\n---> No se encontraron coincidencias.\n\n";
		system("pause");
	}
	delete filtrado;
}

void Interfaz::filtrarPorBookmarks(Historial& his) {
	Historial* filtrado = his.historialFiltradoPorBookmark();
	if (filtrado->existenPestanas())
		navegarFiltros(*filtrado);
	else {
		std::cout << "\n---> No se encontraron coincidencias.\n\n";
		system("pause");
	}
	delete filtrado;
}

void Interfaz::mostrarSitiosEncontrados(Historial& his) {
	system("cls");
	std::cout << "-----Coincidencias Encontradas-----\n";
	if (his.existenPestanas())
		std::cout << his.toString() << '\n';
	else
		std::cout << "---> No se encontraron coincidencias.\n\n";
	system("pause");
}

void Interfaz::mostrarSitiosFiltrados(Historial& his) {
	system("cls");
	his.verificaExpiraciones();
	std::cout << "--------TIGRESTORIAL Filtrado--------\n\n";
	mostrarPagina(his);
	std::cout << "\n---> Utilice las flechas para moverse entre pestañas y sitios\n";
	std::cout << "---> Presione ESC para quitar el filtro\n\n";
}

void Interfaz::navegarFiltros(Historial& his) {
	mostrarSitiosFiltrados(his);
	while (true) {

		if (his.verificaExpiraciones()) {
			system("cls");
			mostrarSitiosFiltrados(his);
		}
		
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			if (!his.moverPestanaSiguiente()) {
				std::cout << "\nNo hay pestañas siguientes\n\n";
				system("pause");
			}
			mostrarSitiosFiltrados(his);
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if (!his.moverPestanaAnterior()) {
				std::cout << "\nNo hay pestañas anteriores\n\n";
				system("pause");
			}
			mostrarSitiosFiltrados(his);
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			if (!his.moverSitioAnterior()) {
				std::cout << "\nNo hay sitios anteriores\n\n";
				system("pause");
			}
			mostrarSitiosFiltrados(his);
			Sleep(200);
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			if (!his.moverSitioSiguiente()) {
				std::cout << "\nNo hay sitios siguientes\n\n";
				system("pause");
			}
			mostrarSitiosFiltrados(his);
			Sleep(200);
		}
		Sleep(100); // Retraso para evitar múltiples entradas rápidas 

		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			return;
	}
}

void Interfaz::cambiarLimiteEntradas(Historial& his) {
	int lim;
	std::cout << "\n\nEscriba el nuevo límite: ";
	do {
		lim = revisaInt();
		if (lim < 1)
			std::cout << "---> El límite debe ser mayor a 0.\n";
	} while (lim < 1);
	Configuracion* config = Configuracion::getInstancia();
	config->setLimite(lim);
	his.actualizarLimites(lim); // Se actualizan los límites de entrada de cada pestaña
}

void Interfaz::cambiarLimiteTiempo(Historial& his) {
	int lim;
	std::cout << "\n\nEscriba el nuevo límite: ";
	do {
		lim = revisaInt();
		if (lim < 1)
			std::cout << "---> El límite debe ser mayor a 0.\n";
	} while (lim < 1);
	Configuracion* config = Configuracion::getInstancia();
	config->setTiempo(std::chrono::seconds(lim));
}

void Interfaz::serializar(Historial& his) {
	std::cout << "Ingrese el nombre de la sesión a guardar (sin extensión): ";
	std::string nombre = revisarString();
	std::ofstream archivo(nombre + ".dat", std::ios::binary);

	if (archivo.fail())
		std::cout << "No se puede abrir el archivo\n\n";
	else {
		his.serializarHistorial(archivo);
		archivo.close();
		std::cout << "Sesión " << nombre << " guardada correctamente.\n\n";
		system("pause");
	}
}

void Interfaz::deserializar(Historial& his) {
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
			his.deserializarHistorial(archivo);
			archivo.close();
			std::cout << "Sesión cargada correctamente.\n\n";
		}
	}
}
std::string Interfaz::revisarString() { // Revisa que la cadena ingresada por el usuario sea válida
	std::string texto;
	bool valido = false;

	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	// Esta funcion limpia el buffer para que cualquier caracter que haya 
	// sido escrito no se muestre al digitar una opcion valida en la navegación.

	while (!valido) {
		try {
			std::getline(std::cin, texto);
			// Usamos std::all_of para comprobar si todos los caracteres son espacios
			if (texto.empty() || std::all_of(texto.begin(), texto.end(), isspace))
				throw ExcCadVacia();
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

int Interfaz::revisaInt() {  // Revisa que el número ingresado por el usuario sea válido
	int num;
	bool valido = false;
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	while (!valido) {
		try {
			// Verifica que la entrada sea válida (un número entero sin caracteres)
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

void Interfaz::mostrarPagina(Historial& his) {
	std::cout << his.mostrarPestana();
}

void Interfaz::mensajeFueraDeRango() {
	std::cout << "\nLa opción digitada está fuera de rango\n\n";
	system("pause");
}

/*
Recursos utilizados

Funcionamiento función isspace():
https://www.tutorialspoint.com/isspace-function-in-cplusplus

Definición de all_off:
https://en.cppreference.com/w/cpp/algorithm/all_any_none_of

Función para detectar entradas del teclado en tiempo real:
https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate#example

Documentación de AmiBroker sobre GetAsyncKeyState (Códigos de teclas virtuales):
https://www.amibroker.com/guide/afl/getasynckeystate.html

Uso de la función FlushConsoleInputBuffer
https://learn.microsoft.com/en-us/windows/console/flushconsoleinputbuffer
*/