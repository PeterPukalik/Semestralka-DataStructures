#include <iostream>
#include <Windows.h>
#include <map>





#include "../libds/heap_monitor.h"
#include "uzemnaJednotka.h"
#include "loader.h"
#include "filter.h"



int main() {


    initHeapMonitor();
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);

    Loader* loader = new Loader();
    Filter* filter = new Filter();
    

    std::map<std::string, uzemnaJednotka*>* obce = new std::map<std::string,uzemnaJednotka*>();
    std::map<std::string, uzemnaJednotka*>* okresy = new std::map<std::string,uzemnaJednotka*>();
    std::map<std::string, uzemnaJednotka*>* kraje = new std::map<std::string,uzemnaJednotka*>();


    loader->loadObce(obce);
    loader->loadOkresy(okresy,obce);
    loader->loadKraje(kraje,okresy);

    bool end = false;
    int control = 0;
    int filterNumber = 0;
    std::map<std::string, uzemnaJednotka*>* temp = new std::map<std::string, uzemnaJednotka*>();
    std::string prefix = "";



    while (!end) {
        std::cout << "tvoje moznosti su:\n 1.filtrovat \n 2.end \n zadaj cislo pre pokracovanie \n ";
        std::cin >> control;
        switch (control) {
        case 1:
            std::cout << "zvolil si filtrovanie \n mas moznost: \n 1. pre filtrovanie startwithStr \n 2. pre filtrovanie containsStr \n";
            std::cin >> filterNumber;
            switch (filterNumber) {
            case 1:
                std::cout << "zadaj slovo na ktore ma zacinat \n";
                std::cin >> prefix;
                filter->findNameWithProperty(temp, obce->begin(), obce->end(), [&prefix](const auto& entry)
                    {
                        if (entry.first.length() < prefix.length()) {
                            return false;
                        }

                // Check if the first prefix.length() characters of str match prefix
                for (size_t i = 0; i < prefix.length(); ++i) {
                    if (entry.first[i] != prefix[i]) {
                        return false;
                    }
                }

                return true;
                    });
                filter->findNameWithProperty(temp, okresy->begin(), okresy->end(), [&prefix](const auto& entry)
                    {
                        if (entry.first.length() < prefix.length()) {
                            return false;
                        }

                // Check if the first prefix.length() characters of str match prefix
                for (size_t i = 0; i < prefix.length(); ++i) {
                    if (entry.first[i] != prefix[i]) {
                        return false;
                    }
                }

                return true;
                    });
                filter->findNameWithProperty(temp, kraje->begin(), kraje->end(), [&prefix](const auto& entry)
                    {
                        if (entry.first.length() < prefix.length()) {
                            return false;
                        }

                // Check if the first prefix.length() characters of str match prefix
                for (size_t i = 0; i < prefix.length(); ++i) {
                    if (entry.first[i] != prefix[i]) {
                        return false;
                    }
                }

                return true;
                    });

                for (const auto& elem : *temp)
                {
                    std::cout << elem.second->getName() << " " << elem.second->getCode() << " " << elem.second->getParent() << "\n";
                    //std::cout << elem.second->toString();
                }
                temp->clear();
                filterNumber = 0;
                break;
            case 2:
                std::cout << "zadaj slovo ktore ma obashovat \n";
                std::cin >> prefix;
                filter->findNameWithProperty(temp, obce->begin(), obce->end(), [&prefix](const auto& entry)
                    {
                        if (entry.first.length() < prefix.length()) {
                            return false;
                        }

                        if (entry.first.find(prefix) != std::string::npos) {
                            return true;
                        }
                        else {
                            return false;
                        }
                    });
                filter->findNameWithProperty(temp, okresy->begin(), okresy->end(), [&prefix](const auto& entry)
                    {
                        if (entry.first.length() < prefix.length()) {
                            return false;
                        }
                        if (entry.first.find(prefix) != std::string::npos) {
                            return true;
                        }
                        else {
                            return false;
                        }
                    });
                filter->findNameWithProperty(temp, kraje->begin(), kraje->end(), [&prefix](const auto& entry)
                    {
                        if (entry.first.length() < prefix.length()) {
                            return false;
                        }

                        if (entry.first.find(prefix) != std::string::npos) {
                            return true;
                        }
                        else {
                            return false;
                        }
                    });

                for (const auto& elem : *temp)
                {
                    std::cout << elem.second->getName() << " " << elem.second->getCode() << " " << elem.second->getParent()<< "\n";
                    //std::cout << elem.second->toString();
                }
                temp->clear();
                filterNumber = 0;

                break;
            default:
                std::cout << "invalid input";
                std::cin >> filterNumber;
                break;
            }
            break;
        case 2:
            std::cout << "\n zvolil si end.";
            end = true;

            break;
        default:
            std::cout << "invalid input \n";
            std::cin >> control;
            break;
        }

    
    }



    delete loader;
    for (auto& item : *obce) {
        delete item.second;
    }
    delete obce;
    for (auto& item : *okresy) {
        delete item.second;
    }
    delete okresy;
    for (auto& item : *kraje) {
        delete item.second;
    }
    delete kraje;
    delete temp;
    delete filter;

    //std::cout << "Hello World!";
    return 0;
}