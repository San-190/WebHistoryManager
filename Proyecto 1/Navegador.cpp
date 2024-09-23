#include "Navegador.h"

Navegador::Navegador(): configuracion(new Configuracion(10,600)){
    privado = false;
    pestanas = new std::list<Pestana*>;
    sitios = new std::vector<Sitio*>;
    bookmarks = new std::list<Sitio*>;
    pestanas->push_back(new Pestana);
    iterador = pestanas->begin();
}

Navegador::Navegador(const Configuracion& conf) : configuracion((Configuracion*)& conf) {
    privado = false;
    pestanas = new std::list<Pestana*>;
    sitios = new std::vector<Sitio*>;
    bookmarks = new std::list<Sitio*>;
    pestanas->push_back(new Pestana);
    iterador = pestanas->begin();
}

Navegador::~Navegador() {
    eliminaTodo();
    if (sitios) {
        for (auto p : *sitios) {
            delete p;
        }
        delete sitios;
    }
}

void Navegador::eliminaTodo() {
    if (configuracion)
        delete configuracion;
    if (pestanas) {
        for (auto p : *pestanas) {
            delete p;
        }
        delete pestanas;
    }
    if (bookmarks) {
        delete bookmarks;
    }
}

void Navegador::agregarPestana(Pestana& p) {
    if (privado)
        p.setIncognito(true);
    pestanas->push_back((Pestana*)&p);
    iterador = --pestanas->end();
}

void Navegador::agregarSitioAPestana(Sitio& sitio){
    (*iterador)->agregarSitio(sitio);
}

void Navegador::agregarSitio(const Sitio& p) {
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
            bookmarks->remove(nuevo);
        }
    }
}

bool Navegador::agregarTag(std::string& s){
    Sitio* sitio= getSitioActual();
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

    auto it = std::lower_bound(sitios->begin(), sitios->end(), sitio,[](const Sitio* a, const Sitio* b) {
        return *a < *b;
    });

    delete sitio;

    if (it != sitios->end() && (*it)->getUrl() == url) {
        return *it;
    }
    return nullptr;
}

void Navegador::leerSitios(std::ifstream& archivo) {
    const size_t tam = 2048;
    char buffer[tam];
    std::string url, titulo, atributo;

    while (archivo.read(buffer, tam) || archivo.gcount() > 0) {
        size_t bytes = archivo.gcount();
        for (size_t i = 0; i < bytes; ++i) {
            char c = buffer[i];

            if (c == ',') {
                url = atributo;
                atributo.clear();
            }
            else if (c == '\n') {
                titulo = atributo;
                sitios->push_back(new Sitio(url, titulo));  
                url.clear();
                titulo.clear();
                atributo.clear();
            }
            else {
                atributo += c; 
            }
        }
    }
    std::sort(sitios->begin(), sitios->end(), [](const Sitio* a, const Sitio* b) {
        return *a < *b;
        });
}

std::string Navegador::mostrarPestana(){
    std::string s = "";
    if (privado)
        s = "   Modo Incognito Activado\n\n";
    if (*iterador != nullptr){
        return s + (*iterador)->mostrarPestana();
    }
    return "No hay pestañas\n";
}

bool Navegador::moverPestanaAnterior(){
    if (pestanas->empty())
        return false;

    if (iterador != pestanas->begin()) {
        iterador--; 
        return true;
    }
    else
        return false;
}

bool Navegador::moverPestanaSiguiente(){
    if (pestanas->empty())
        return false;

    iterador++;
    if (iterador != pestanas->end())
        return true;
    else{
        iterador--;
        return false;
    }
}

bool Navegador::moverSitioAnterior(){
    return (*iterador)->moverSitioAnterior();
}

bool Navegador::moverSitioSiguiente(){
    return (*iterador)->moverSitioSiguiente();
}

void Navegador::cambiarModoIncognito(){
    if (privado)
        desactivarModoIncognito();
    else
        activarModoIncognito();
}

void Navegador::activarModoIncognito(){
    privado = true;
    agregarPestana(*new Pestana);
    incognito = iterador;
}

void Navegador::desactivarModoIncognito(){
    bool bandera = false;
    privado = false;
    Pestana* aux = nullptr;
    while (incognito != pestanas->end()) {
        if (!bandera && iterador == incognito)
            bandera = true;
        Pestana::numero--;
        aux = *incognito;
        incognito++;
        pestanas->remove(aux);
        delete aux;
    }
    if (bandera)
        iterador = --pestanas->end();
}

Sitio* Navegador::getSitioActual(){
    return (*iterador)->getSitioActual();
}

void Navegador::serializarNavegador(std::ofstream& archivo) {
    archivo.write(reinterpret_cast<const char*>(&privado), sizeof(privado));
    if (privado) {
        int num = (*incognito)->getNumero();
        archivo.write(reinterpret_cast<const char*>(&num), sizeof(num));
    }

    size_t tam = pestanas->size();
    archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));

    for (auto pestana : *pestanas)
        pestana->serializarPestana(archivo);

    for (auto sitio : *bookmarks) {
        std::string url = sitio->getUrl();
        tam = url.size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(url.c_str(), tam);

        Bookmark* bookmark = sitio->getBookmark();
        bookmark->serializarBookmark(archivo);
    }

    configuracion->serializarConfiguracion(archivo);
}

void Navegador::deserializarNavegador(std::ifstream& archivo) {
    eliminaTodo();
    archivo.read(reinterpret_cast<char*>(&privado), sizeof(privado));
    int num = 0;

    if (privado)
        archivo.read(reinterpret_cast<char*>(&num), sizeof(num));

    deserializarPestana(archivo, num);

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

    configuracion->deserializarConfiguracion(archivo);
}

void Navegador::deserializarPestana(std::ifstream& archivo, int num) {
    size_t tam;
    archivo.read(reinterpret_cast<char*>(&tam), sizeof(tam));

    for (size_t i = 1; i <= tam; ++i) {
        Pestana* pestana = new Pestana();
        bool ing;
        int id;

        archivo.read(reinterpret_cast<char*>(&ing), sizeof(ing));
        pestana->setIncognito(ing);
        archivo.read(reinterpret_cast<char*>(&id), sizeof(id));
        pestana->setNumero(id);

        size_t can=0;
        archivo.read(reinterpret_cast<char*>(can), sizeof(can));

        for (size_t i = 1; i <= can; ++i) {
            size_t caracteres;
            archivo.read(reinterpret_cast<char*>(&caracteres), sizeof(caracteres));

            std::string url(caracteres, ' ');
            archivo.read(&url[0], caracteres);

            Sitio* sitio = buscarSitio(url);
            sitios->push_back(sitio);
        }

        pestanas->push_back(pestana);
        if (i == num)
            incognito = --pestanas->end();
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
*/