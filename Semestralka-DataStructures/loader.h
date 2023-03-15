#pragma once


#include <fstream>
#include <map>
#include <iostream>



#include "uzemnaJednotka.h"




class Loader {
public:
	Loader();
	~Loader();



	void loadKraje(std::map<std::string, uzemnaJednotka*>* kraje, std::map<std::string, uzemnaJednotka*>* okresy);
	void loadOkresy(std::map<std::string, uzemnaJednotka*>* okresy, std::map<std::string, uzemnaJednotka*>* obce);
	void loadObce(std::map<std::string, uzemnaJednotka*>* obce);
	

};




inline Loader::Loader()
{
}

inline Loader::~Loader()
{
}

inline void Loader::loadKraje(std::map<std::string, uzemnaJednotka*>* kraje, std::map<std::string, uzemnaJednotka*>* okresy) {
	std::ifstream file;
	std::string filename = "C:\\Users\\pukal\\source\\repos\\Semestralka-DataStructures\\kraje.csv";
	file.open(filename, std::ios::in);
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
		kraje->insert(std::pair < std::string, uzemnaJednotka*>(name, uzemnJ));

		for (auto& item : *okresy) {
			if (item.second->getCode().substr(3,1).compare(code) == 0) { //substr ( odkial, kolko )
				item.second->setParent(name);
			}

		}



		//delete uzemnJ;

	}

	file.close();

}

inline void Loader::loadOkresy(std::map<std::string, uzemnaJednotka*>* okresy, std::map<std::string, uzemnaJednotka*>* obce) {

	std::ifstream file;
	std::string filename = "C:\\Users\\pukal\\source\\repos\\Semestralka-DataStructures\\okresy.csv";
	file.open(filename, std::ios::in);
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
		okresy->insert(std::pair < std::string, uzemnaJednotka*>(name, uzemnJ));
		for (auto& item : *obce) {
			if (item.second->getCode().substr(0, 6) == code) {
				item.second->setParent(name);
			}
		}


		//delete uzemnJ;

	}

	file.close();

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
		//delete uzemnJ;

	}

	file.close();
}