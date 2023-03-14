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



	template<typename Iterator>
	//std::map<std::string, uzemnaJednotka*>* findNameWithProperty(std::map<std::string, uzemnaJednotka*>* predicate,Iterator begin, Iterator end,Function func) const;
	void findNameWithProperty(std::map<std::string, uzemnaJednotka*>* predicate,Iterator begin, Iterator end, std::function<bool(std::pair<const std::string, uzemnaJednotka*>)> func ) const;


};

inline Filter::Filter() 
{
}

inline Filter::~Filter()
{
}

template<typename Iterator>
inline void Filter::findNameWithProperty(std::map<std::string, uzemnaJednotka*>* predicate, Iterator begin, Iterator end, std::function<bool(std::pair<const std::string, uzemnaJednotka*>)> func) const
{
    for (Iterator it = begin; it != end; ++it) {
        if (func(*it)) {
            //std::string name = (*it).first;
            //*predicate->operator[](name) = *it->second;
            predicate->insert(std::pair < std::string, uzemnaJednotka*>((*it).first, (*it).second));
        }
    }
}
