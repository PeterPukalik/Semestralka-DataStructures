#pragma once


#include <fstream>
#include <map>
#include <iostream>



#include "uzemnaJednotka.h"
#include <libds/amt/implicit_hierarchy.h>
#include <libds/adt/table.h>


#include <libds/amt/explicit_hierarchy.h>
#include <libds/adt/tree.h>
#include <libds/constants.h>

#include <functional>


class Loader {
public:
	Loader();
	~Loader();


	void loadObce(std::vector<uzemnaJednotka*>* obce);
	void loadOkresy(std::vector<uzemnaJednotka*>* okresy, std::vector<uzemnaJednotka*>* obce);
	void loadKraje(std::vector<uzemnaJednotka*>* kraje, std::vector<uzemnaJednotka*>* okresy);	
	void loadSlovensko(std::vector<uzemnaJednotka*>* slovensko, std::vector<uzemnaJednotka*>* kraje);


	void loadObceH(ds::amt::MultiWayExplicitHierarchy<uzemnaJednotka*>* hierarchy, std::vector<uzemnaJednotka*>* obce);
	void loadOkresyH(ds::amt::MultiWayExplicitHierarchy<uzemnaJednotka*>* hierarchy, std::vector<uzemnaJednotka*>* okresy);
	void loadKrajeH(ds::amt::MultiWayExplicitHierarchy<uzemnaJednotka*>* hierarchy, std::vector<uzemnaJednotka*>* kraje);
	void loadSlovenskoH(ds::amt::MultiWayExplicitHierarchy<uzemnaJednotka*>* hierarchy, std::vector<uzemnaJednotka*>* slovensko);

	void loadObceT(ds::adt::Treap<std::string, uzemnaJednotka*>* table, std::vector<uzemnaJednotka*>* obce);
	void loadOkresyT(ds::adt::Treap<std::string, uzemnaJednotka*>* table, std::vector<uzemnaJednotka*>* okresy);
	void loadKrajeT(ds::adt::Treap<std::string, uzemnaJednotka*>* table, std::vector<uzemnaJednotka*>* kraje);
	void loadSlovenskoT(ds::adt::Treap<std::string, uzemnaJednotka*>* table, std::vector<uzemnaJednotka*>* slovensko);

};




inline Loader::Loader()
{
}

inline Loader::~Loader()
{
}

inline void Loader::loadKraje(std::vector<uzemnaJednotka*>* kraje, std::vector<uzemnaJednotka*>* okresy) {
	std::ifstream file;
	std::string filename = "C:\\Users\\pukal\\source\\repos\\AUS-VS2022\\Semestralka-DataStructures\\kraje.csv";
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
			if (item->getCode() == "SKZZZZ" || item->getCode() == "SKZZZ") {
				item->setParent("Zahranièie");
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
			item->setParent("Zahranièie");
		}
	
	}

}



inline void Loader::loadObceH(ds::amt::MultiWayExplicitHierarchy<uzemnaJednotka*>* hierarchy, std::vector<uzemnaJednotka*>* obce)
{
	size_t index = 0;
	size_t indexSave = 0;
	size_t krajIndex = 0;
	size_t okresIndex = 0;

	auto root = hierarchy->accessRoot();
	auto krajNode = hierarchy->accessSon(*root, krajIndex);
	auto okresNode = hierarchy->accessSon(*krajNode, okresIndex);

	for (auto obec : *obce) {
		
		if (okresNode->data_->getName() != obec->getParent()) {
			++okresIndex;
			index = 0;
			//if (hierarchy->accessSon(*krajNode, okresIndex)->sons_->indexOfNext(okresIndex) == std::numeric_limits<size_t>::max()) {  // Access parent's sons
			if (hierarchy->accessSon(*krajNode, okresIndex)==nullptr) {  // Access parent's sons
				++krajIndex;
				okresIndex = 0;
				if (hierarchy->accessSon(*root, krajIndex)->sons_->indexOfNext(0) == std::numeric_limits<size_t>::max()) { // Access root's sons
					// Error: Parent not found in the hierarchy
					std::cout << "Error: Parent not found in the hierarchy." << std::endl;
					return;
				}
				krajNode = hierarchy->accessSon(*root, krajIndex);
			}
			okresNode = hierarchy->accessSon(*krajNode, okresIndex);
		}
		//std::cout << okresNode->data_->getName() << " " << obec->getName() << "-" << obec->getParent() << "\n";
		if (okresNode != nullptr && okresNode->data_->getName() == obec->getParent()) {
			hierarchy->emplaceSon(*okresNode, index);
			hierarchy->accessSon(*okresNode, index)->data_ = obce->at(indexSave);
			++index;
			++indexSave;
		}
	}
}




inline void Loader::loadOkresyH(ds::amt::MultiWayExplicitHierarchy<uzemnaJednotka*>* hierarchy, std::vector<uzemnaJednotka*>* okresy)
{
	//size_t index = 0;
	//size_t krajIndex = 0;
	//bool stop = false;
	//for (auto okres : *okresy) {
	//	krajIndex = 0;
	//	stop = false; // Initialize stop to false at the start of each iteration
	//	while (krajIndex < 9 && !stop) {
	//		if (hierarchy->accessSon(*hierarchy->accessRoot(), krajIndex)->data_->getName() == okres->getParent()) {
	//			// Check if the parent object exists in the hierarchy before establishing child relationship
	//			hierarchy->emplaceSon(*hierarchy->accessSon(*hierarchy->accessRoot(), krajIndex), index);
	//			hierarchy->accessSon(*hierarchy->accessSon(*hierarchy->accessRoot(), krajIndex), index)->data_ = okresy->at(index);
	//			index++;
	//			stop = true;
	//		}
	//		++krajIndex;
	//	}
	//}

	size_t index = 0;
	size_t indexSave = 0;
	size_t krajIndex = 0;
	for (auto okres : *okresy) {

		if (hierarchy->accessSon(*hierarchy->accessRoot(), krajIndex)->data_->getName() == okres->getParent()) {
			// Check if the parent object exists in the hierarchy before establishing child relationship
			hierarchy->emplaceSon(*hierarchy->accessSon(*hierarchy->accessRoot(), krajIndex), index);
			hierarchy->accessSon(*hierarchy->accessSon(*hierarchy->accessRoot(), krajIndex), index)->data_ = okresy->at(indexSave);
			index++;
			indexSave++;
		}
		else {
			++krajIndex;
			index = 0;

			if ((hierarchy->accessSon(*hierarchy->accessRoot(), krajIndex)->data_->getName() == okres->getParent())) {
				// Check if the parent object exists in the hierarchy before establishing child relationship
				hierarchy->emplaceSon(*hierarchy->accessSon(*hierarchy->accessRoot(), krajIndex), index);
				hierarchy->accessSon(*hierarchy->accessSon(*hierarchy->accessRoot(), krajIndex), index)->data_ = okresy->at(indexSave);
				index++;
				indexSave++;
			}

		}


	}


}


inline void Loader::loadKrajeH(ds::amt::MultiWayExplicitHierarchy<uzemnaJednotka*>* hierarchy, std::vector<uzemnaJednotka*>* kraje)
{
	size_t index = 0;
	bool stop = false;
	while (!stop) {
		if (index == 9) {
			stop = true;
			break;
		}
		hierarchy->emplaceSon(*hierarchy->accessRoot(), index);
		hierarchy->accessSon(*hierarchy->accessRoot(), index)->data_ = kraje->at(index);
		index++;
	}
	

}

inline void Loader::loadSlovenskoH(ds::amt::MultiWayExplicitHierarchy<uzemnaJednotka*>* hierarchy, std::vector<uzemnaJednotka*>* slovensko)
{
	//uzemnaJednotka* uzemnJ = new uzemnaJednotka();
	//uzemnJ->setCode("SK");
	//uzemnJ->setName("Slovensko");
	hierarchy->emplaceRoot();
	hierarchy->accessRoot()->data_ = slovensko->at(0);

}

inline void Loader::loadObceT(ds::adt::Treap<std::string, uzemnaJednotka*>* table, std::vector<uzemnaJednotka*>* obce)
{
	for (auto item : *obce) {
		table->insertWithDuplicates(item->getName(), item);
	}
}

inline void Loader::loadOkresyT(ds::adt::Treap<std::string, uzemnaJednotka*>* table, std::vector<uzemnaJednotka*>* okresy)
{
	for (auto item : *okresy) {
		table->insertWithDuplicates(item->getName(), item);
	}
}

inline void Loader::loadKrajeT(ds::adt::Treap<std::string, uzemnaJednotka*>* table, std::vector<uzemnaJednotka*>* kraje)
{
	for (auto item : *kraje) {
		table->insertWithDuplicates(item->getName(), item);

	}
}

inline void Loader::loadSlovenskoT(ds::adt::Treap<std::string, uzemnaJednotka*>* table, std::vector<uzemnaJednotka*>* slovensko)
{
	for (auto item : *slovensko) {
		table->insertWithDuplicates(item->getName(), item);
	}
}

inline void Loader::loadOkresy(std::vector<uzemnaJednotka*>* okresy, std::vector<uzemnaJednotka*>* obce) {

	std::ifstream file;
	std::string filename = "C:\\Users\\pukal\\source\\repos\\AUS-VS2022\\Semestralka-DataStructures\\okresy.csv";
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
	std::string filename = "C:\\Users\\pukal\\source\\repos\\AUS-VS2022\\Semestralka-DataStructures\\obceWithDuplicatescsv.csv";
	//std::string filename = "C:\\Users\\pukal\\source\\repos\\AUS-VS2022\\Semestralka-DataStructures\\obce.csv";
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