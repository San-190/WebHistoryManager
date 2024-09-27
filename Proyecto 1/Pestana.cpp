#include "Pestana.h"

int Pestana::numero = 1;

Pestana::Pestana() {
	sitios = new std::list<Limitador*>;
	iterador = sitios->begin();
	id = numero++;
}

Pestana::~Pestana() {
	numero--;
	if (sitios) {
		for (auto s : *sitios) {
			delete s;
		}
		delete sitios;
	}
}

int Pestana::getId() { return id; }

void Pestana::setId(int num) { id = num; }

std::list<Limitador*>* Pestana::getSitios() { return sitios; }

void Pestana::agregarSitio(Sitio& sitio, std::chrono::time_point<std::chrono::steady_clock> exp) {
	Configuracion* config = Configuracion::getInstancia();
	Limitador* nuevo = new Limitador(sitio);
	if (exp != std::chrono::steady_clock::time_point())
		nuevo->setTiempoInicio(exp);

	if (config->getLimite() <= sitios->size()) {  // En caso de que el límite de sitios en la configuración sea superado
		auto primero = sitios->begin();			 // Se elimina el primer sitio de la pestaña, y se agrega de último el nuevo
		delete* primero;
		sitios->erase(primero);
		if(!sitios->empty())
			iterador = --sitios->end();
	}
	if (sitios->empty()) {
		sitios->push_back(nuevo);
		iterador = sitios->begin();
	}
	else {
		Sitio* s = (*iterador)->getSitio();
		if (s->getUrl() != sitio.getUrl()) {
			sitios->push_back(nuevo);
			iterador = --sitios->end();
		}
		else
			(*iterador)->setTiempoInicio(std::chrono::steady_clock::now()); // Si se intenta ingresar al últmio sitio que se visitó, se resetea su timer
	}
}

void Pestana::actualizaTamano(size_t tam) {
	size_t t = sitios->size();
	while (t > tam) {
		auto primero = sitios->begin();
		delete* primero;
		sitios->erase(primero);
		t--;
	}
	if(!sitios->empty())
		iterador = --sitios->end();
}

std::string Pestana::mostrarPestana() {
	std::stringstream s;
	s << "       Pestaña #" << id;
	if (sitios->empty())
		s << "\nNo hay sitios actualmente.\n\n";
	else {
		Sitio* sitio = (*iterador)->getSitio();
		s << sitio->toString();
	}
	return s.str();
}

Sitio* Pestana::getSitioActual() {
	if (!sitios->empty())
		return (*iterador)->getSitio();
	return nullptr;
}

bool Pestana::moverSitioAnterior() {
	if (sitios->empty())
		return false;
	if (iterador != sitios->begin()) {
		iterador--;
		return true;
	}
	else
		return false;
}

bool Pestana::moverSitioSiguiente() {
	if (sitios->empty())
		return false;

	iterador++;
	if (iterador != sitios->end())
		return true;
	else {
		iterador--;
		return false;
	}
}

void Pestana::serializarPestana(std::ofstream& archivo) {
	archivo.write(reinterpret_cast<const char*>(&id), sizeof(id));

	size_t tam = sitios->size();
	archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));

	for (const auto& s : *sitios) {
		Sitio* sitio = s->getSitio();
		std::string url = sitio->getUrl();
		tam = url.size();
		archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
		archivo.write(url.c_str(), tam);
	}
}

bool Pestana::quitarSitiosExpirados() {
	bool bandera = false;
	auto actual = std::chrono::steady_clock::now();
	Configuracion* config = Configuracion::getInstancia();
	std::chrono::seconds tiempoFinal(config->getTiempo());
	// Eliminar los elementos que han expirado
	for (auto it = sitios->begin(); it != sitios->end();) {
		if (std::chrono::duration_cast<std::chrono::seconds>(actual - (*it)->getTiempoInicio()) >= tiempoFinal) {
			delete* it;
			it = sitios->erase(it);
			bandera = true;
		}
		else
			it++;
	}
	if(bandera && !sitios->empty())
		iterador = --sitios->end();
	return bandera;
}

/*
Recursos utilizados

Uso de std::chrono::duration_cast:
https://en.cppreference.com/w/cpp/chrono/duration/duration_cast
*/