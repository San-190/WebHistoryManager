#pragma once
#include <fstream>
#include <sstream>
#include <vector>

class Bookmark{
private:
	std::vector<std::string*>* tags;

public:
	Bookmark();
	virtual ~Bookmark();
	std::vector<std::string*>* getTags();
	bool existe(std::string&);
	bool agregarTag(std::string& tag);
	bool eliminarTag(std::string& tag);
	void serializarBookmark(std::ofstream&);
	std::string toString();
};

