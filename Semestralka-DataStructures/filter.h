#pragma once
#include <map>
#include <string>
#include "uzemnaJednotka.h"
#include <functional>
#include <iterator>

class Filter {
public:

	Filter();
	~Filter();



	template<typename Iterator,typename Function>
	//std::map<std::string, uzemnaJednotka*>* findNameWithProperty(std::map<std::string, uzemnaJednotka*>* predicate,Iterator begin, Iterator end,Function func) const;
	void findNameWithProperty(std::map<std::string, uzemnaJednotka*>* predicate,Iterator begin, Iterator end,Function func) const;


};

inline Filter::Filter() 
{
}

inline Filter::~Filter()
{
}

template<typename Iterator,typename Function>
inline void Filter::findNameWithProperty(std::map<std::string, uzemnaJednotka*>* predicate, Iterator begin, Iterator end, Function func) const
{
	for (Iterator it = begin; it != end; ++it) {
		if (func) {
			std::string name = (*it).first;
			//i want to save to predicate on possiton [name] same thing as in (*it)
		}
	}
}
