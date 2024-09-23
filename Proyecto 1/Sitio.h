#pragma once
#include <iostream>
#include <sstream>
#include "Bookmark.h"

class Sitio {
private:
    std::string url;
    std::string titulo;
    Bookmark* bookmark;

public:
    Sitio(std::string = "", std::string = "");
    ~Sitio();

    std::string getUrl() const;
    std::string getTitulo() const;
    Bookmark* getBookmark();

    void setUrl(const std::string&);
    void setTitulo(const std::string&);
    void setBookmark(Bookmark&);
    bool agregarTag(std::string&);
    bool quitarTag(std::string&);

    std::string toString();

    void quitarBookmark();

    bool operator<(const Sitio&) const;
};