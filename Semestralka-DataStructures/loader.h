#pragma once


#include <fstream>
#include <map>
#include <iostream>



#include "uzemnaJednotka.h"




class Loader {
public:
	Loader();
	~Loader();


	void loadObce(std::vector<uzemnaJednotka*>* obce);
	void loadOkresy(std::vector<uzemnaJednotka*>* okresy, std::vector<uzemnaJednotka*>* obce);
	void loadKraje(std::vector<uzemnaJednotka*>* kraje, std::vector<uzemnaJednotka*>* okresy);	
	void loadSlovensko(std::vector<uzemnaJednotka*>* slovensko, std::vector<uzemnaJednotka*>* kraje);
	

};




inline Loader::Loader()
{
}

inline Loader::~Loader()
{
}

inline void Loader::loadKraje(std::vector<uzemnaJednotka*>* kraje, std::vector<uzemnaJednotka*>* okresy) {
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
		std::getline(file, str, ';');

		std::getline(file, name, ';');

		std::getline(file, str, ';');
		std::getline(file, str, ';');

		std::getline(file, code);
		//std::getline(file, str);


		uzemnaJednotka* uzemnJ = new uzemnaJednotka();
		uzemnJ->setCode(code);
		uzemnJ->setName(name);
		//std::cout << name << " " << code << "\n";

		/*obce->insert(std::map<std::string, uzemnaJednotka*>::value_type(name, uzemnJ));*/
		kraje->push_back(uzemnJ);
		for (auto& item : *okresy) {
			if (item->getCode().substr(0,5).compare(code.substr(5,9)) == 0) { //substr ( odkial, kolko )
				item->setParent(name);
			}

		}



		//delete uzemnJ;

	}

	file.close();

}

inline void Loader::loadSlovensko(std::vector<uzemnaJednotka*>* slovensko, std::vector<uzemnaJednotka*>* kraje)
{





	uzemnaJednotka* uzemnJ = new uzemnaJednotka();
	uzemnJ->setCode("SK");
	uzemnJ->setName("Slovensko");
	slovensko->push_back(uzemnJ);
	for (auto& item : *kraje) {
		if (item->getCode() != "ZZ-9-*****") {
			item->setParent("Slovensko");
		}
		else {
			item->setParent("Zahranicie");
		}
	
	}

}

inline void Loader::loadOkresy(std::vector<uzemnaJednotka*>* okresy, std::vector<uzemnaJednotka*>* obce) {

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
		okresy->push_back(uzemnJ);
		for (auto& item : *obce) {
			if (item->getCode().substr(0, 6) == code) {
				item->setParent(name);
			}
		}


		//delete uzemnJ;

	}

	file.close();

}

inline void Loader::loadObce(std::vector<uzemnaJednotka*>* obce) {


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
		obce->push_back(uzemnJ);
		//delete uzemnJ;

	}

	file.close();
}