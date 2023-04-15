#include <iostream>

#include <vector>
#include <iomanip>

#include "uzemnaJednotka.h"
#include "loader.h"
#include "filter.h"



//  #include <libds/adt/abstract_data_type.h>
//#include <libds/adt/array.h>
//#include <libds/adt/list.h>
//#include <libds/adt/priority_queue.h>
//#include <libds/adt/queue.h>
//#include <libds/adt/sorts.h>
//#include <libds/adt/stack.h>
//#include <libds/adt/table.h>


//#include <libds/amt/abstract_memory_type.h>
//#include <libds/amt/explicit_hierarchy.h>
//#include <libds/amt/explicit_network.h>
//#include <libds/amt/explicit_sequence.h>
//#include <libds/amt/hierarchy.h>
#include <libds/amt/implicit_hierarchy.h>
//#include <libds/amt/implicit_sequence.h>
//#include <libds/amt/network.h>
//#include <libds/amt/sequence.h>

//#include <libds/mm/compact_memory_manager.h>
//#include <libds/mm/memory_manager.h>
//#include <libds/mm/memory_omanip.h>

#include <libds/constants.h>



#include <libds/heap_monitor.h>

#include <libds/adt/tree.h>

#include <Windows.h>


int main() {


    initHeapMonitor();
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);

    Loader* loader = new Loader();
    Filter* filter = new Filter();


    std::vector<uzemnaJednotka*>* obce = new std::vector<uzemnaJednotka*>();
    std::vector<uzemnaJednotka*>* okresy = new std::vector<uzemnaJednotka*>();
    std::vector<uzemnaJednotka*>* kraje = new std::vector<uzemnaJednotka*>();
    std::vector<uzemnaJednotka*>* slovensko = new std::vector<uzemnaJednotka*>();


    ds::amt::MultiWayExplicitHierarchy<uzemnaJednotka*>* hierarchy = new ds::amt::MultiWayExplicitHierarchy<uzemnaJednotka*>();


    loader->loadObce(obce);
    loader->loadOkresy(okresy, obce);
    loader->loadKraje(kraje, okresy);
    loader->loadSlovensko(slovensko, kraje);

    loader->loadSlovenskoH(hierarchy, slovensko);

    std::cout << hierarchy->size() << std::endl;
    loader->loadKrajeH(hierarchy, kraje);

    std::cout << hierarchy->size() << std::endl;
    loader->loadOkresyH(hierarchy, okresy);

    std::cout << hierarchy->size() << std::endl;
    //loader->loadObceH(hierarchy, obce);
    for(auto item : *hierarchy)
{
    std::cout << item->getName() << std::endl;
}
//hierarchy->processLevelOrder(hierarchy->accessRoot(), [](ds::amt::MultiWayExplicitHierarchyBlock<uzemnaJednotka*>* entry) { std::cout << entry->data_->getName() << std::endl; });
//hierarchy->processPreOrder(hierarchy->accessRoot(), [](const ds::amt::MultiWayExplicitHierarchyBlock<uzemnaJednotka*>* entry) {
//    std::cout << entry->data_->getName() << std::endl; // Modify the lambda function to match the expected signature
//    });

    std::cout << hierarchy->size() << std::endl;

    bool end = false;
    int control = 0;
    int filterNumber = 0;

    std::vector<uzemnaJednotka*>* temp = new std::vector<uzemnaJednotka*>();
    std::string prefix = "";



    while (!end) {
        std::cout << "tvoje moznosti su:\n 1.filtrovat \n 0.end \n zadaj cislo pre pokracovanie \n ";
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
                        //if (entry..length() < prefix.length()) {
                        if (entry->getName().length() < prefix.length()) {
                            return false;
                        }

                        // Check if the first prefix.length() characters of str match prefix
                        for (size_t i = 0; i < prefix.length(); ++i) {
                            if (entry->getName()[i] != prefix[i]) {
                                return false;
                            }
                        }

                        return true;
                    });
                filter->findNameWithProperty(temp, okresy->begin(), okresy->end(), [&prefix](const auto& entry)
                    {
                        if (entry->getName().length() < prefix.length()) {
                            return false;   
                        }

                        // Check if the first prefix.length() characters of str match prefix
                        for (size_t i = 0; i < prefix.length(); ++i) {
                            if (entry->getName()[i] != prefix[i]) {
                                return false;
                            }
                        }

                        return true;
                            });
                filter->findNameWithProperty(temp, kraje->begin(), kraje->end(), [&prefix](const auto& entry)
                    {
                        if (entry->getName().length() < prefix.length()) {
                            return false;
                        }

                        // Check if the first prefix.length() characters of str match prefix
                        for (size_t i = 0; i < prefix.length(); ++i) {
                            if (entry->getName()[i] != prefix[i]) {
                                return false;
                            }
                        }

                        return true;
                            });

                for (const auto& elem : *temp)
                {
                    std::cout << std::left << std::setw(30) << elem->getName() << " | "
                        << std::setw(30) << elem->getParent() << " | "
                        << std::setw(30) << elem->getCode() << "\n";
                }
                temp->clear();
                filterNumber = 0;
                break;
            case 2:
                std::cout << "zadaj slovo ktore ma obashovat \n";
                std::cin >> prefix;
                filter->findNameWithProperty(temp, obce->begin(), obce->end(), [&prefix](const auto& entry)
                    {
                        if (entry->getName().length() < prefix.length()) {
                            return false;
                        }

                        if (entry->getName().find(prefix) != std::string::npos) {
                            return true;
                        }
                        else {
                            return false;
                        }
                    });
                filter->findNameWithProperty(temp, okresy->begin(), okresy->end(), [&prefix](const auto& entry)
                    {
                        if (entry->getName().length() < prefix.length()) {
                            return false;
                        }

                        if (entry->getName().find(prefix) != std::string::npos) {
                            return true;
                        }
                        else {
                            return false;
                        }
                    });
                filter->findNameWithProperty(temp, kraje->begin(), kraje->end(), [&prefix](const auto& entry)
                    {
                        if (entry->getName().length() < prefix.length()) {
                            return false;
                        }

                        if (entry->getName().find(prefix) != std::string::npos) {
                            return true;
                        }
                        else {
                            return false;
                        }
                    });
                for (const auto& elem : *temp)
                {
                    std::cout << std::left << std::setw(30) << elem->getName() << " | "
                        << std::setw(30) << elem->getParent() << " | "
                        << std::setw(30) << elem->getCode() << "\n";
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
        case 0:
            std::cout << "\n zvolil si end.";
            end = true;

            break;
        default:
            std::cout << "invalid input \n";
            std::cin >> control;
            break;
        }

    
    }




    for (auto& item : *obce) {
        delete item;
    }
    delete obce;
    for (auto& item : *okresy) {
        delete item;
    }
    delete okresy;
    for (auto& item : *kraje) {
        delete item;
    }  
    for (auto& item : *slovensko) {
        delete item;
    }
    delete slovensko;

    delete hierarchy;
    delete kraje;
    delete temp;
    delete filter;
    delete loader;

    //std::cout << "Hello World!";
    return 0;
}