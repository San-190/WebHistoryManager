#include "Pestana.h"

int Pestana::numero = 1;

Pestana::Pestana() {
	incognito = false;
	sitios = new std::list<Limitador*>;
	iterador = sitios->begin();
	id = numero++;
}

Pestana::~Pestana() {
	if (sitios) {
		for (auto s : *sitios)
			delete s;
		delete sitios;
	}
}

int Pestana::getNumero() { return id; }

void Pestana::setNumero(int num) { id = num; }

bool Pestana::getIncognito() {
	return incognito;
}

void Pestana::setIncognito(bool in) {
	incognito = in;
}

std::list<Limitador*>* Pestana::getSitios() { return sitios; }

void Pestana::agregarSitio(Limitador& lim) {
	Configuracion* config = Configuracion::getInstancia();
	if (config->getLimite() <= sitios->size()) {
		auto primero = sitios->begin();
		delete* primero;
		sitios->erase(primero);
	}
	if (sitios->empty()) {
		sitios->push_back(&lim);
		iterador = sitios->begin();
	}
	else {
		Sitio* s = (*iterador)->getSitio();
		Sitio* n = lim.getSitio();
		if (s->getUrl() != n->getUrl()) {
			sitios->push_back(&lim);
			iterador = --sitios->end();
		}
	}
}

void Pestana::actualizaTamano(size_t tam) {
	size_t t = sitios->size();
	while (tam <= t) {
		auto primero = sitios->begin();
		delete* primero;
		sitios->erase(primero);
		t--;
	}
	iterador = --sitios->end();
}

std::string Pestana::mostrarPestana() {
	std::stringstream s;
	s << "       Pestaña #" << id;
	if (incognito)
		s << " (Incógnita)";
	if (sitios->empty())
		s << "\nBusque una página\n\n";
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
	archivo.write(reinterpret_cast<const char*>(&incognito), sizeof(incognito));
	archivo.write(reinterpret_cast<const char*>(&id), sizeof(id));

	size_t tam = sitios->size();
	archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));

	for (const auto& s : *sitios) {
		std::chrono::time_point<std::chrono::steady_clock> tiempo = s->getTiempoInicio();
		archivo.write(reinterpret_cast<const char*>(&tiempo), sizeof(tiempo));

		Sitio* sitio = s->getSitio();
		std::string url = sitio->getUrl();
		tam = url.size();
		archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
		archivo.write(url.c_str(), tam);
	}
}

void Pestana::quitarSitiosExpirados() {
	auto actual = std::chrono::steady_clock::now();
	Configuracion* config = Configuracion::getInstancia();
	std::chrono::seconds tiempoFinal(config->getTiempo());
	// Eliminar los elementos que han expirado
	for (auto it = sitios->begin(); it != sitios->end();) {
		if (std::chrono::duration_cast<std::chrono::seconds>(actual - (*it)->getTiempoInicio()) >= tiempoFinal) {
			delete* it;
			it = sitios->erase(it);
		}
		else
			it++;
	}
}
