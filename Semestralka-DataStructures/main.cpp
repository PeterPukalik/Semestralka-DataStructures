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


    loader->loadObce(obce);
    //for (auto& entry : *obce) {
    //    std::cout << "{" << entry.first << ", " << entry.second << "}" << std::endl;
    //}

    
    delete loader;
    delete obce;

    std::cout << "Hello World!";
    return 0;
}