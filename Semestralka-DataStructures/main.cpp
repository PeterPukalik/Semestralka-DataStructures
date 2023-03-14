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
    loader->loadOkresy(okresy);
    loader->loadKraje(kraje);

    bool end = false;
    int control = 0;
    int filterNumber = 0;
    std::map<std::string, uzemnaJednotka*>* temp = new std::map<std::string, uzemnaJednotka*>();
    while (!end) {
        std::cout << "tvoje moznosti su:\n 1.filtrovat \n 2.end \n zadaj cislo pre pokracovanie \n ";
        std::cin >> control;
        switch (control) {
        case 1:
            std::cout << "zvolil si filtrovanie \n mas moznost: \n 1. pre filtrovanie startwithStr \n 2. pre filtrovanie containsStr";
            std::cin >> filterNumber;
            switch (filterNumber) {
            case 1:
                filter->findNameWithProperty(temp, obce->begin(), obce->end(), [](){});
                filter->findNameWithProperty(temp, okresy->begin(), okresy->end(), []() {});
                filter->findNameWithProperty(temp, kraje->begin(), kraje->end(), []() {});
                break;
            case 2:
                break;
            default:
                break;
            }
            break;
        case 2:
            std::cout << "\n zvolil si end.";
            end = true;

            break;
        default:
            break;
        }

    
    }



    delete loader;
    delete obce;
    delete okresy;
    delete kraje;
    delete temp;

    //std::cout << "Hello World!";
    return 0;
}