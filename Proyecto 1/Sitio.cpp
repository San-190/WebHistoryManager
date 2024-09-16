#include "Sitio.h"

Sitio::Sitio(std::string u, std::string t, bool bm, std::string tg)
    :url(u), titulo(t), bookmark(bm), tag(tg) {}

Sitio::~Sitio() {}

std::string Sitio::getUrl() const { return url; }

std::string Sitio::getTitulo() const { return titulo; }

bool Sitio::getBookmark() const { return bookmark; }

std::string Sitio::getTag() const { return tag; }

void Sitio::setUrl(const std::string& u) { url = u; }

void Sitio::setTitulo(const std::string& t) { titulo = t; }

void Sitio::setBookmark(bool bm) { bookmark = bm; }

void Sitio::setTag(const std::string& tg) { tag = tg; }

bool Sitio::operator<(const Sitio& sitio) const{
    return url < sitio.url;
}