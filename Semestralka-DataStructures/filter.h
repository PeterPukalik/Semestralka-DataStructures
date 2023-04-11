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
	void findNameWithProperty(std::vector<uzemnaJednotka*>* data,Iterator begin, Iterator end, std::function<bool(uzemnaJednotka*)> predicate ) const;


};

inline Filter::Filter() 
{
}

inline Filter::~Filter()
{

}

template<typename Iterator>
inline void Filter::findNameWithProperty(std::vector<uzemnaJednotka*>* data, Iterator begin, Iterator end, std::function<bool(uzemnaJednotka*)> predicate) const
{
    for (Iterator it = begin; it != end; ++it) {
        if (predicate(*it)) {
            //std::string name = (*it).first;
            //*predicate->operator[](name) = *it->second;
            data->push_back((*it));//pridat lambdu
        }
    }
}
