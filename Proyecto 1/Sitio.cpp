#include "Sitio.h"

Sitio::Sitio(std::string u , std::string t)
    :url(u) , titulo(t) {}

Sitio::~Sitio() {
    if(bookmark)
        delete bookmark;
}

std::string Sitio::getUrl() const { return url; }

std::string Sitio::getTitulo() const { return titulo; }

Bookmark* Sitio::getBookmark(){ return bookmark; }


void Sitio::setUrl(const std::string& u) { url = u; }

void Sitio::setTitulo(const std::string& t) { titulo = t; }

void Sitio::setBookmark(Bookmark& book){
    bookmark = &book;
}

bool Sitio::agregarTag(std::string& s){
    if (bookmark) {
        return bookmark->agregarTag(s);
    }
    return false;
}

bool Sitio::quitarTag(std::string& s){
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

void Sitio::quitarBookmark(){
    delete bookmark;
    bookmark = nullptr;
}

bool Sitio::operator<(const Sitio& sitio) const{
    return url < sitio.url;
}