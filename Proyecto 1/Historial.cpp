#include "Historial.h"

Historial::Historial(){
    pestanas = new std::list<Pestana*>;
    sitios = nullptr; // Este vector se inicializa al leer los Sitios desde el .csv
    bookmarks = new std::vector<Sitio*>;
}

void Historial::inicializarHistorial() {
    pestanas->push_back(new Pestana()); // Siempre habrá como mínimo una Pestaña abierta
    iterador = pestanas->begin();
}

Historial* Historial::historialFiltradoPorUrlTitulo(std::string buscado) {
    verificaExpiracionesEnTodas(); // Elimina los Sitios que hayan cumplido sus tiempos de expiración
    Historial* filtrado = new Historial();
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
        if (bandera) { // Si en la Pestaña había un Sitio con coincidencias, se agrega al Historial filtrado
            filtrado->agregarPestana(*pestana);
            bandera = false;
        }
        else
            delete pestana;
    }
    filtrado->moverPestanaInicial();
    return filtrado;
}

Historial* Historial::historialFiltradoPorBookmark() {
    Historial* filtrado = new Historial();
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
    filtrado->moverPestanaInicial();
    return filtrado;
}

Historial::~Historial() {
    reiniciar();
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

void Historial::reiniciar() {
    if (pestanas) {
        for (auto p : *pestanas)
            delete p;
        pestanas->clear();
    }
    if (bookmarks) {
        for (auto b : *bookmarks)
            b->quitarBookmark();
        bookmarks->clear();
    }
}

void Historial::agregarPestana(Pestana& p) {
    pestanas->push_back((Pestana*)&p);
    iterador = --pestanas->end();
}

void Historial::agregarSitioAPestana(Sitio& sitio) {
    (*iterador)->agregarSitio(sitio);
}

void Historial::agregarSitio(Sitio& p) {
    sitios->push_back((Sitio*)&p);
}

void Historial::agregarQuitarBookmark() {
    Sitio* nuevo = getSitioActual();
    if (nuevo) {
        if (!nuevo->getBookmark()) { // Si el Sitio actual, no tiene Bookmark, se le agrega
            nuevo->setBookmark(*(new Bookmark()));
            bookmarks->push_back(nuevo);
        }
        else {
            nuevo->quitarBookmark(); // Sí tenía Bookmark, se lo quitamos y lo eliminamos del contenedor
            for (auto it = bookmarks->begin(); it != bookmarks->end(); it++)
                if (nuevo->getUrl() == (*it)->getUrl()) {
                    bookmarks->erase(it);
                    return;
                }
        }
    }
}

bool Historial::agregarTag(std::string& s) {
    Sitio* sitio = getSitioActual();
    return sitio->agregarTag(s);
}

bool Historial::quitarTag(std::string& s){
    Sitio* sitio = getSitioActual();
    return sitio->quitarTag(s);
}

Sitio* Historial::buscarSitio(std::string url) {
    Sitio* sitio = new Sitio(); // Sitio auxiliar para realizar la búsqueda comparando por URL
    sitio->setUrl(url);

    // lower_bound busca al primer elemento mayor o igual al buscado (estando la lista ordenada)
    // Como cuarto parámetro, se recibe un lambda, que es una función de comparación personalizada.
    auto it = std::lower_bound(sitios->begin(), sitios->end(), sitio, [](const Sitio* a, const Sitio* b) {
        return *a < *b;
    });

    delete sitio;

    // Sí el iterador no fue más allá del final de la colección y tiene el URL buscado, se retorna el Sitio
    if (it != sitios->end() && (*it)->getUrl() == url)
        return *it;
    return nullptr;
}

void Historial::leerSitios(std::ifstream& archivo) {
    if(!sitios)
        sitios = new std::vector<Sitio*>;

    // La lectura se realiza por medio de búfferes de 2048 bytes
    const size_t tam = 2048;
    char buffer[tam];

    std::string url = "", dominio = "", titulo = "", atributo = "";

    // gcount devuelve la cantidad de caracteres leídos
    while (archivo.read(buffer, tam) || archivo.gcount() > 0) {
        size_t bytes = archivo.gcount();
        // Se recorren los caracteres leídos en búsqueda de comas o saltos de línea
        for (size_t i = 0; i < bytes; ++i) {
            char c = buffer[i];

            if (c == ',') { // Sí se encuentra una coma, significa que tenemos un atributo completo para asignar
                if (url == "")
                    url = atributo;
                else
                    dominio = atributo;
                atributo = "";
            }
            else if (c == '\n') { // Al encontrar un salto de línea, se termina de leer el sitio y se agrega al vector
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
    // Una vez terminada la lectura, se ordenan los sitios para poder utilizar correctamente lower_bound
    std::sort(sitios->begin(), sitios->end(), [](const Sitio* a, const Sitio* b) {
        return *a < *b;
    });
}

std::string Historial::mostrarPestana() {
    std::string s = "";
    if (*iterador != nullptr)
        return s + (*iterador)->mostrarPestana();
    return "No hay pestañas\n";
}

void Historial::moverPestanaInicial(){
    if (!pestanas->empty())
        iterador = pestanas->begin();
}

bool Historial::moverPestanaAnterior() {
    if (pestanas->empty())
        return false;

    if (iterador != pestanas->begin()) {
        iterador--;
        return true;
    }
    else
        return false;
}

bool Historial::moverPestanaSiguiente() {
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

bool Historial::moverSitioAnterior() {
    return (*iterador)->moverSitioAnterior();
}

bool Historial::moverSitioSiguiente() {
    return (*iterador)->moverSitioSiguiente();
}

void Historial::setSitios(std::vector<Sitio*>* sit){
    sitios = sit;
}

std::vector<Sitio*>* Historial::getSitios() {
    return sitios;
}

Sitio* Historial::getSitioActual() {
    return (*iterador)->getSitioActual();
}

Pestana* Historial::getPestanaActual() {
    return (*iterador);
}

void Historial::actualizarLimites(int lim){
    for (auto p : *pestanas)
        p->actualizaTamano(lim);
}

bool Historial::verificaExpiraciones(){
    Pestana* p = getPestanaActual();
    return p->quitarSitiosExpirados();
}

void Historial::verificaExpiracionesEnTodas(){
    for (auto p : *pestanas)
        p->quitarSitiosExpirados();
}

bool Historial::existenPestanas() {
    if (pestanas)
        return !pestanas->empty();
    return false;
}

std::string Historial::toString() {
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

void Historial::serializarHistorial(std::ofstream& archivo) {
    // Se serializa el tamaño de todos los contenedores para saber cuantas veces realizar la lectura corresspondiente
    size_t tam = pestanas->size();
    archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));

    for (auto pestana : *pestanas)
        pestana->serializarPestana(archivo);

    tam = bookmarks->size();
    archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));

    for (auto sitio : *bookmarks) {
        // Como los Sitios ya están guardados en el archivo csv, aquí solo guardamos su URL y su Bookmark
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

void Historial::deserializarHistorial(std::ifstream& archivo) {
    reiniciar(); // Se borran los elementos que existieran antes de cargar
    deserializarPestanas(archivo);

    size_t tam;
    archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));

    for (size_t i = 1; i <= tam; ++i) {
        size_t caracteres;
        archivo.read(reinterpret_cast<char*>(&caracteres), sizeof(caracteres));

        // Se inicializa un string (con espacios vacíos) del tamaño adecuado
        std::string url(caracteres, ' ');
        // Se lee desde el primer caracter hasta el último
        archivo.read(&url[0], caracteres);

        // Una vez leído el URL, se busca el Sitios en el vector de Sitios para agregarle el Bookmark
        Sitio* sitio = buscarSitio(url);
        bookmarks->push_back(sitio);

        Bookmark* bookmark = new Bookmark();
        deserializarBookmark(archivo, *bookmark);
        sitio->setBookmark(*bookmark);
    }
    Configuracion* configuracion = Configuracion::getInstancia();
    configuracion->deserializarConfiguracion(archivo);

    iterador = pestanas->begin(); // Una vez terminada la lectura, se coloca el iterador en la primera Pestaña
}

void Historial::deserializarPestanas(std::ifstream& archivo) {
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


void Historial::deserializarBookmark(std::ifstream& archivo, Bookmark& bookmark) {
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