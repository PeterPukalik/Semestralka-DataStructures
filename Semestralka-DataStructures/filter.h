#pragma once
#include <map>
#include <string>
#include "uzemnaJednotka.h"
#include <functional>
#include <iterator>

#include <libds/amt/implicit_hierarchy.h>
#include <libds/adt/sorts.h>


class Filter {
public:

	Filter();
	~Filter();



	//template<typename Iterator>
	////std::map<std::string, uzemnaJednotka*>* findNameWithProperty(std::map<std::string, uzemnaJednotka*>* predicate,Iterator begin, Iterator end,Function func) const;
	//void findNameWithProperty(std::vector<uzemnaJednotka*>* data,Iterator begin, Iterator end, std::function<bool(uzemnaJednotka*)> predicate ) const;

    template <typename Iterator>
    void findNameWithProperty(std::vector<uzemnaJednotka*>* data, Iterator begin, Iterator end, std::function<bool(uzemnaJednotka*)> predicate) const;

    //template<typename Iterator, typename Item>
    //void findNameWithPropertyT(std::vector<ds::adt::TreapItem<std::string, uzemnaJednotka*>*>* data, Iterator begin, Iterator end, std::function<bool(Item*)> predicate);

    template< typename Iterator, typename T>
    void findNameWithPropertyUniversal(std::vector<T>* data, Iterator begin, Iterator end, std::function<bool(T)> predicate);


};

inline Filter::Filter() 
{
}

inline Filter::~Filter()
{

}




template< typename Iterator, typename T>
inline void Filter::findNameWithPropertyUniversal(std::vector<T>* data, Iterator begin, Iterator end, std::function<bool(T)> predicate) {
    for (Iterator it = begin; it != end; ++it) {
        if (predicate(*it)) {
            data->push_back(*it);
        }
    }
}

template<typename Iterator>
inline void Filter::findNameWithProperty(std::vector<uzemnaJednotka*>* data, Iterator begin, Iterator end, std::function<bool(uzemnaJednotka*)> predicate) const
{
    for (Iterator it = begin; it != end; ++it) {
        if (predicate(*it)) {
            //std::string name = (*it).first;
            //*predicate->operator[](name) = *it->second;
            data->push_back((*it));//pridat lambdu
            //data->insertLast();
            //data->accessLast()->data_ = *it;
        }
    }
}

//template<typename Iterator, typename Item>
//inline void Filter::findNameWithPropertyT(std::vector<ds::adt::TreapItem<std::string, uzemnaJednotka*>*>* data, Iterator begin, Iterator end, std::function<bool(Item*)> predicate)
//{
//    for (Iterator it = begin; it != end; ++it) {
//        //if (predicate((*it).data_)) {
//        if (predicate(&(*it))) {
//            //std::string name = (*it).first;
//            //*predicate->operator[](name) = *it->second;
//            data->push_back((&(*it)));//pridat lambdu
//            //data->insertLast();
//            //data->accessLast()->data_ = &(*it);
//        }
//    }
//}
