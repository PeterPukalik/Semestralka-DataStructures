#include <iostream>
#include <Windows.h>
#include <map>





#include "../libds/heap_monitor.h"
#include "uzemnaJednotka.h"
#include "loader.h"



int main() {


    initHeapMonitor();
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);
    setlocale(LC_ALL, "slovak");

    Loader* loader = new Loader();
    

    std::map<std::string, uzemnaJednotka*>* obce = new std::map<std::string,uzemnaJednotka*>();
    std::map<std::string, uzemnaJednotka*>* okresy = new std::map<std::string,uzemnaJednotka*>();
    std::map<std::string, uzemnaJednotka*>* kraje = new std::map<std::string,uzemnaJednotka*>();


    loader->loadObce(obce);
    loader->loadOkresy(okresy);
    loader->loadKraje(kraje);
    for (auto& entry : *kraje) {
        std::cout << "{" << entry.first << ", " << entry.second << "}" << std::endl;
    }

    
    delete loader;
    delete obce;
    delete okresy;
    delete kraje;

    //std::cout << "Hello World!";
    return 0;
}