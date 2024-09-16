#include"Controladora.h"

int main(int argc, char* argv[]) {
	setlocale(LC_CTYPE, "Spanish");
	Controladora* controladora = new Controladora;
	controladora->principalControl0();
	delete controladora;
	return 0;
}