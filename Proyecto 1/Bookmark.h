#pragma once
#include <string>
#include <sstream>
#include <vector>

class Bookmark
{
private:
	std::vector<std::string*>* tags;

public:
	Bookmark();
	virtual ~Bookmark();
	bool existe(std::string &);
	bool agregarTag(std::string& tag);
	bool eliminarTag(std::string& tag);
	std::string toString();

};

