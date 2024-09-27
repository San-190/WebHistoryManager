#include "Navegador.h"

Navegador::Navegador(){
    pestanas = new std::list<Pestana*>;
    sitios = nullptr;
    bookmarks = new std::vector<Sitio*>;
}

void Navegador::inicializarNavegador() {
    pestanas->push_back(new Pestana());
    iterador = pestanas->begin();
}

Navegador* Navegador::navegadorFiltradoPorUrlTitulo(std::string buscado) {
    verificaExpiracionesEnTodas();
    Navegador* filtrado = new Navegador();
    Sitio* sitio = nullptr;
    std::string url = "", titulo = "";
    bool bandera = false;
    int i = 1;

    for (auto p : *pestanas) {
        Pestana* pestana = new Pestana();
        pestana->setId(i++);
        for (auto s : *(p)->getSitios()) {
            sitio = s->getSitio();
            url = sitio->getUrl();
            titulo = sitio->getTitulo();
            // find retorna la posición de la primera ocurrencia de la subcadena en la cadena.
            // npos es un valor especial que indica que la subcadena no fue encontrada.
            if (url.find(buscado) != std::string::npos || titulo.find(buscado) != std::string::npos) {
                pestana->agregarSitio(*sitio, s->getTiempoInicio());
                bandera = true;
            }
        }
        if (bandera) {
            filtrado->agregarPestana(*pestana);
            bandera = false;
        }
        else
            delete pestana;
    }
    return filtrado;
}

Navegador* Navegador::navegadorFiltradoPorBookmark() {
    Navegador* filtrado = new Navegador();
    bool bandera = false;
    int i = 1;
    for (auto p : *pestanas) {
        Pestana* pestana = new Pestana();
        pestana->setId(i++);
        for (auto s : *(p)->getSitios()) {
            Sitio* sitio = s->getSitio();
            if (sitio->getBookmark()) {
                pestana->agregarSitio(*sitio);
                bandera = true;
            }
        }
        if (bandera) {
            filtrado->agregarPestana(*pestana);
            bandera = false;
        }
        else
            delete pestana;
    }
    return filtrado;
}

Navegador::~Navegador() {
    eliminaTodo();
    if (sitios) {
        for (auto p : *sitios)
            delete p;
        delete sitios;
    }
    if (pestanas)
        delete pestanas;
    if (bookmarks)
        delete bookmarks;
}

void Navegador::eliminaTodo() {
    if (pestanas) {
        for (auto p : *pestanas) {
            delete p;
        }
        pestanas->clear();
    }
    if (bookmarks) {
        for (auto b : *bookmarks)
            b->quitarBookmark();
        bookmarks->clear();
    }
}

void Navegador::agregarPestana(Pestana& p) {
    pestanas->push_back((Pestana*)&p);
    iterador = --pestanas->end();
}

void Navegador::agregarSitioAPestana(Sitio& sitio) {
    (*iterador)->agregarSitio(sitio);
}

void Navegador::agregarSitio(Sitio& p) {
    sitios->push_back((Sitio*)&p);
}

void Navegador::agregarQuitarBookmark() {
    Sitio* nuevo = getSitioActual();
    if (nuevo) {
        if (!nuevo->getBookmark()) {
            nuevo->setBookmark(*(new Bookmark()));
            bookmarks->push_back(nuevo);
        }
        else {
            nuevo->quitarBookmark();
            for (auto i = bookmarks->begin(); i != bookmarks->end(); i++)
                if (nuevo->getUrl() == (*i)->getUrl()) {
                    bookmarks->erase(i);
                    return;
                }
        }
    }
}

bool Navegador::agregarTag(std::string& s) {
    Sitio* sitio = getSitioActual();
    return sitio->agregarTag(s);
}

bool Navegador::quitarTag(std::string& s)
{
    Sitio* sitio = getSitioActual();
    return sitio->quitarTag(s);
}

Sitio* Navegador::buscarSitio(std::string url) {
    Sitio* sitio = new Sitio();
    sitio->setUrl(url);

    auto it = std::lower_bound(sitios->begin(), sitios->end(), sitio, [](const Sitio* a, const Sitio* b) {
        return *a < *b;
        });

    delete sitio;

    if (it != sitios->end() && (*it)->getUrl() == url) {
        return *it;
    }
    return nullptr;
}

void Navegador::leerSitios(std::ifstream& archivo) {
    sitios = new std::vector<Sitio*>;
    const size_t tam = 2048;
    char buffer[tam];
    std::string url = "", dominio = "", titulo = "", atributo = "";

    while (archivo.read(buffer, tam) || archivo.gcount() > 0) {
        size_t bytes = archivo.gcount();
        for (size_t i = 0; i < bytes; ++i) {
            char c = buffer[i];

            if (c == ',') {
                if (url == "")
                    url = atributo;
                else
                    dominio = atributo;
                atributo = "";
            }
            else if (c == '\n') {
                titulo = atributo;
                sitios->push_back(new Sitio(url, dominio, titulo));
                url = "";
                dominio = "";
                titulo = "";
                atributo = "";
            }
            else
                atributo += c;
        }
    }
    std::sort(sitios->begin(), sitios->end(), [](const Sitio* a, const Sitio* b) {
        return *a < *b;
        });
}

std::string Navegador::mostrarPestana() {
    std::string s = "";
    if (*iterador != nullptr) {
        return s + (*iterador)->mostrarPestana();
    }
    return "No hay pestañas\n";
}

bool Navegador::moverPestanaAnterior() {
    if (pestanas->empty())
        return false;

    if (iterador != pestanas->begin()) {
        iterador--;
        return true;
    }
    else
        return false;
}

bool Navegador::moverPestanaSiguiente() {
    if (pestanas->empty())
        return false;

    iterador++;
    if (iterador != pestanas->end())
        return true;
    else {
        iterador--;
        return false;
    }
}

bool Navegador::moverSitioAnterior() {
    return (*iterador)->moverSitioAnterior();
}

bool Navegador::moverSitioSiguiente() {
    return (*iterador)->moverSitioSiguiente();
}

void Navegador::setSitios(std::vector<Sitio*>* sit){
    sitios = sit;
}

std::vector<Sitio*>* Navegador::getSitios() {
    return sitios;
}

Sitio* Navegador::getSitioActual() {
    return (*iterador)->getSitioActual();
}

Pestana* Navegador::getPestanaActual() {
    return (*iterador);
}

void Navegador::actualizarLimites(int lim){
    for (auto p : *pestanas)
        p->actualizaTamano(lim);
}

bool Navegador::verificaExpiraciones(){
    Pestana* p = getPestanaActual();
    return p->quitarSitiosExpirados();
}

void Navegador::verificaExpiracionesEnTodas(){
    for (auto p : *pestanas)
        p->quitarSitiosExpirados();
}

bool Navegador::existenPestanas() {
    if (pestanas)
        return !pestanas->empty();
    return false;
}

std::string Navegador::mostrarBookmarks() {
    std::stringstream s;
    if (bookmarks && !bookmarks->empty())
        for (auto b : *bookmarks)
            s << b->toString();
    else
        s << "Actualmente no hay bookamrks.\n";
    return s.str();
}

std::string Navegador::toString() {
    std::stringstream s;
    for (auto p : *pestanas) {
        s << "\n---> Pestaña #" << p->getId() << '\n';
        for (auto sit : *p->getSitios()) {
            Sitio* sitio = sit->getSitio();
            s << sitio->toString();
        }
    }
    return s.str();
}

void Navegador::serializarNavegador(std::ofstream& archivo) {
    size_t tam = pestanas->size();
    archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));

    for (auto pestana : *pestanas)
        pestana->serializarPestana(archivo);

    tam = bookmarks->size();
    archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
    for (auto sitio : *bookmarks) {
        std::string url = sitio->getUrl();
        tam = url.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        // c_str() convierte el string a un const char* para serializarlo
        archivo.write(url.c_str(), tam);

        Bookmark* bookmark = sitio->getBookmark();
        bookmark->serializarBookmark(archivo);
    }
    Configuracion* configuracion = Configuracion::getInstancia();
    configuracion->serializarConfiguracion(archivo);
}

void Navegador::deserializarNavegador(std::ifstream& archivo) {
    eliminaTodo();
    deserializarPestana(archivo);

    size_t tam;
    archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));

    for (size_t i = 1; i <= tam; ++i) {
        size_t caracteres;
        archivo.read(reinterpret_cast<char*>(&caracteres), sizeof(caracteres));

        // Se inicializa un string (con espacios vacíos) del tamaño adecuado
        std::string url(caracteres, ' ');
        // Se lee desde el primer caracter hasta el último
        archivo.read(&url[0], caracteres);

        Sitio* sitio = buscarSitio(url);
        bookmarks->push_back(sitio);

        Bookmark* bookmark = new Bookmark();
        deserializarBookmark(archivo, *bookmark);
        sitio->setBookmark(*bookmark);
    }
    Configuracion* configuracion = Configuracion::getInstancia();
    configuracion->deserializarConfiguracion(archivo);
    iterador = pestanas->begin();
}

void Navegador::deserializarPestana(std::ifstream& archivo) {
    size_t tam;
    archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));

    for (size_t i = 1; i <= tam; ++i) {
        Pestana* pestana = new Pestana();
        int id;

        archivo.read(reinterpret_cast<char*>(&id), sizeof(id));
        pestana->setId(id);

        size_t can=0;
        archivo.read(reinterpret_cast<char*>(&can), sizeof(can));

        for (size_t i = 1; i <= can; ++i) {
            size_t caracteres;
            archivo.read(reinterpret_cast<char*>(&caracteres), sizeof(caracteres));

            std::string url(caracteres, ' ');
            archivo.read(&url[0], caracteres);

            Sitio* sitio = buscarSitio(url);
            pestana->agregarSitio(*sitio);
        }

        pestanas->push_back(pestana);
    }
}


void Navegador::deserializarBookmark(std::ifstream& archivo, Bookmark& bookmark) {
    size_t tam;
    archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));

    for (size_t i = 0; i < tam; ++i) {
        size_t caracteres;
        archivo.read(reinterpret_cast<char*>(&caracteres), sizeof(caracteres));

        std::string tag(caracteres, ' ');
        archivo.read(&tag[0], caracteres);

        bookmark.agregarTag(tag);
    }
}

/*
Recursos utilizados

Funcionamiento de upper_bound y lower_bound: 
https://www.geeksforgeeks.org/upper_bound-and-lower_bound-for-vector-in-cpp-stl/

Definición y uso de funciones lambdas:
https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170

Uso de las funciones find() y npos():
https://www.geeksforgeeks.org/stringnpos-in-c-with-examples/
https://www.geeksforgeeks.org/string-find-in-cpp/
*/