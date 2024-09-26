#include "Sitio.h"

Sitio::Sitio(std::string u, std::string d, std::string t)
    :url(u), dominio(d), titulo(t), bookmark(nullptr) {}

Sitio::~Sitio() {
    if (bookmark)
        delete bookmark;
}

std::string Sitio::getUrl() { return url; }

std::string Sitio::getTitulo() { return titulo; }

std::string Sitio::getDominio() { return dominio; }

Bookmark* Sitio::getBookmark() { return bookmark; }


void Sitio::setUrl(std::string& u) { url = u; }

void Sitio::setTitulo(std::string& t) { titulo = t; }

void Sitio::setDominio(std::string d) { dominio = d; }

void Sitio::setBookmark(Bookmark& book) {
    bookmark = &book;
}

bool Sitio::agregarTag(std::string& s) {
    if (bookmark) {
        return bookmark->agregarTag(s);
    }
    return false;
}

bool Sitio::quitarTag(std::string& s) {
    if (bookmark) {
        return bookmark->eliminarTag(s);
    }
    return false;
}

std::string Sitio::toString() {
    std::stringstream s;
    s << '\n' << url << '\n';
    s << titulo << '\n';
    if (bookmark)
        s << "Favorito * \n"
        << bookmark->toString() << '\n';
    return s.str();
}

void Sitio::quitarBookmark() {
    delete bookmark;
    bookmark = nullptr;
}

bool Sitio::operator<(const Sitio& sitio) const {
    return url < sitio.url;
}