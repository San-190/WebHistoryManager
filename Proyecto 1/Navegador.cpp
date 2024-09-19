#include "Navegador.h"

Navegador::Navegador(): configuracion(new Configuracion(10,600)){
    pestanas = new std::list<Pestana*>;
    sitios = new std::vector<Sitio*>;
    bookmarks = new std::list<Sitio*>;
    pestanas->push_back(new Pestana(1));
    iterador = pestanas->begin();
}

Navegador::Navegador(const Configuracion& conf) : configuracion((Configuracion*)& conf) {
    pestanas = new std::list<Pestana*>;
    sitios = new std::vector<Sitio*>;
    bookmarks = new std::list<Sitio*>;
    pestanas->push_back(new Pestana(1));
    iterador = pestanas->begin();
}

Navegador::~Navegador() {
    if(configuracion)
        delete configuracion;
    if (pestanas) {
        for (auto p : *pestanas) {
            delete p;
        }
        delete pestanas;
    }
    if (sitios) {
        for (auto p : *sitios) {
            delete p;
        }
        delete sitios;
    }
    if (bookmarks) {
        for (auto p : *bookmarks) {
            delete p;
        }
        delete bookmarks;
    }
}

void Navegador::agregarPestana(const Pestana& p) {
    pestanas->push_back((Pestana*)&p);
}

void Navegador::agregarSitio(const Sitio& p) {
    sitios->push_back((Sitio*)&p);
}

void Navegador::agregarBookmark(const Sitio& p) {
    bookmarks->push_back((Sitio*)&p);
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

    std::string atributo, url, titulo, tag;
    bool bookmark = 0;
    int contador = 1;

    while (archivo.read(buffer, tam) || archivo.gcount() > 0) {
        size_t bytes = archivo.gcount();
        for (size_t i = 0; i < bytes; ++i) {
            char c = buffer[i];

            if (c == ',') {
                if (contador == 1) {
                    url = atributo;
                }
                else if (contador == 2) {
                    titulo = atributo;
                }
                else if (contador == 3) {
                    if ("1" == atributo)
                        bookmark = true;
                    else
                        bookmark = false;
                }
                atributo.clear();
                contador++;
            }
            else if (c == '\n') {
                tag = atributo;

                sitios->push_back(new Sitio(url, titulo, bookmark, tag));

                atributo.clear();
                contador = 1;
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

std::string Navegador::mostrarPestana()
{
    if (*iterador != nullptr){
        return (*iterador)->mostrarPestana();
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

/*
Recursos utilizados

Funcionamiento de upper_bound y lower_bound: 
https://www.geeksforgeeks.org/upper_bound-and-lower_bound-for-vector-in-cpp-stl/

Definición y uso de funciones lambdas:
https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170
*/