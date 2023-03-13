#pragma once


#include <fstream>
#include <map>
#include <iostream>



#include "uzemnaJednotka.h"




class Loader {
public:
	Loader();
	~Loader();



	void loadKraje();
	void loadOkresy();
	void loadObce(std::map<std::string, uzemnaJednotka*>* obce);
	

};




inline Loader::Loader()
{
}

inline Loader::~Loader()
{
}

inline void Loader::loadKraje() {

}

inline void Loader::loadOkresy() {

}

inline void Loader::loadObce(std::map<std::string, uzemnaJednotka*>* obce) {


	std::ifstream file;
	std::string filename = "C:\\Users\\pukal\\source\\repos\\Semestralka-DataStructures\\obce.csv";
	file.open(filename,std::ios::in);
	if (!file.is_open())
	{
		throw std::invalid_argument("subor sa nepodarilo otvorit");
	}

	std::string code;
	std::string name;
	std::string str;
	
	std::getline(file, str);


	while (!file.eof()) {

		std::getline(file, str, ';');
		std::getline(file, code, ';');
		std::getline(file, name, ';');


		std::getline(file, str);


		uzemnaJednotka* uzemnJ = new uzemnaJednotka();
		uzemnJ->setCode(code);
		uzemnJ->setName(name);
		//std::cout << name << " " << code << "\n";

		/*obce->insert(std::map<std::string, uzemnaJednotka*>::value_type(name, uzemnJ));*/
		obce->insert(std::pair < std::string, uzemnaJednotka*>(name, uzemnJ));
		delete uzemnJ;

	}

	file.close();
}