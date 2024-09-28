#include "Bookmark.h"

Bookmark::Bookmark(){ tags = new std::vector<std::string*>; }

Bookmark::~Bookmark(){
    if (tags) {
        for (auto p : *tags)
            delete p;
        delete tags;
    }
}

std::vector<std::string*>* Bookmark::getTags() { return tags; }

bool Bookmark::existe(std::string& tag){
    for (auto t : *tags)
        if (*t == tag)
            return true;
    return false;
    
}

bool Bookmark::agregarTag(std::string& tag){
    if (!existe(tag)) {
        tags->push_back(new std::string(tag));
        return true;
    }
    return false;
}

bool Bookmark::eliminarTag(std::string& tag){
    for (auto i = tags->begin(); i != tags->end(); i++) {
        if (**i == tag) {
            delete* i;
            tags->erase(i);
            return true;
        }
    }
    return false;
}

void Bookmark::serializarBookmark(std::ofstream& archivo){
    size_t tam = tags->size();
    archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));

    for (auto tag : *tags) {
        tam = tag->size();
        archivo.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
        archivo.write(tag->c_str(), tam);
    }
}

std::string Bookmark::toString(){
    std::stringstream s;
    if (!tags->empty()) {
        s << "Tags: ";
        for (auto i : *tags)
            s << '#' << *i << ' ';
    }
    return s.str();
}
