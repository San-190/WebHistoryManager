#pragma once
#include <iostream>
#include "Bookmark.h"

class Sitio {
private:
    std::string url;
    std::string dominio;
    std::string titulo;
    Bookmark* bookmark;

public:
    Sitio(std::string = "", std::string = "", std::string = "");
    ~Sitio();

    std::string getUrl();
    std::string getTitulo();
    std::string getDominio();
    Bookmark* getBookmark();

    void setUrl(std::string&);
    void setTitulo(std::string&);
    void setDominio(std::string);
    void setBookmark(Bookmark&);
    bool agregarTag(std::string&);
    bool quitarTag(std::string&);

    std::string toString();

    void quitarBookmark();

    bool operator<(const Sitio&) const;
};