#include"Controladora.h"

/*
	Visual Studio 2022
	Fecha: 29-09-2024
	Universidad Nacional de Costa Rica
	Santiago Araya Espinoza (1-1903-0723)
	Jarren Chaves Vizcaino (1-1870-0594)
	John Blanco Paniagua (1-19250623)

	El objetivo del proyecto es implementar un administrador del historial de navegación de un navegador web.
*/

int main(int argc, char* argv[]) {
	setlocale(LC_CTYPE, "Spanish"); // Permite usar caracteres propios del español
	Controladora* controladora = new Controladora;
	controladora->principalControl0();
	delete controladora;
	_CrtDumpMemoryLeaks();
	// El memory leak que se muestra corresponde a la Configuración (Singleton)
	// Esto se debe a que se elimina por medio de "atexit" (al finalizar el programa)
	return 0;
}