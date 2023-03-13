#pragma once


#include <string>





class uzemnaJednotka {
public:
	//setters
	void setName(std::string nameTemp);
	void setCode(std::string codeTemp);


	//getters
	std::string getName();
	std::string getCode();

private:
	std::string name;
	std::string code;

};


inline void uzemnaJednotka::setName(std::string nameTemp) {
	this->name = nameTemp;
}

inline void uzemnaJednotka::setCode(std::string codeTemp) {
	this->code = codeTemp;
}

inline std::string uzemnaJednotka::getName() {
	return this->name;
}


inline std::string uzemnaJednotka::getCode() {
	return this->code;
}



