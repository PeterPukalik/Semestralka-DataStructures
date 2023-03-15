#pragma once


#include <string>





class uzemnaJednotka {
public:
	//setters
	void setName(std::string nameTemp);
	void setCode(std::string codeTemp);
	void setParent(std::string parentTemp);


	//getters
	std::string getName();
	std::string getCode();
	std::string getParent();

	//tostring
	//std::string toString();

private:
	std::string name;
	std::string code;
	std::string parent;

};


inline void uzemnaJednotka::setName(std::string nameTemp) {
	this->name = nameTemp;
}

inline void uzemnaJednotka::setCode(std::string codeTemp) {
	this->code = codeTemp;
}

inline void uzemnaJednotka::setParent(std::string parentTemp)
{
	this->parent = parentTemp;
}

inline std::string uzemnaJednotka::getName() {
	return this->name;
}


inline std::string uzemnaJednotka::getCode() {
	return this->code;
}

inline std::string uzemnaJednotka::getParent()
{
	return this->parent;
}





