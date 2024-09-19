#pragma once
#include <iostream>
#include<sstream>

class Sitio {
private:
    std::string url;
    std::string titulo;
    bool bookmark;
    std::string tag;

public:
    Sitio(std::string = "", std::string = "", bool = false, std::string = "");
    ~Sitio();

    std::string getUrl() const;
    std::string getTitulo() const;
    bool getBookmark() const;
    std::string getTag() const;

    void setUrl(const std::string&);
    void setTitulo(const std::string&);
    void setBookmark(bool);
    void setTag(const std::string&);

    std::string toString();

    bool operator<(const Sitio&) const;
};