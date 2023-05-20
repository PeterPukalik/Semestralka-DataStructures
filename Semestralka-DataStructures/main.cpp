#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <iomanip>

#include "uzemnaJednotka.h"
#include "loader.h"
#include "filter.h"



//#include <libds/adt/sorts.h>

#include <libds/adt/table.h>

#include <libds/adt/sorts.h>



#include <libds/amt/implicit_hierarchy.h>

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
    ds::adt::ShellSort<uzemnaJednotka*> shellSort;


    std::vector<uzemnaJednotka*>* obce = new std::vector<uzemnaJednotka*>();
    std::vector<uzemnaJednotka*>* okresy = new std::vector<uzemnaJednotka*>();
    std::vector<uzemnaJednotka*>* kraje = new std::vector<uzemnaJednotka*>();
    std::vector<uzemnaJednotka*>* slovensko = new std::vector<uzemnaJednotka*>();

    std::vector<uzemnaJednotka*>* filterVector = obce;


    ds::amt::MultiWayExplicitHierarchy<uzemnaJednotka*>* hierarchy = new ds::amt::MultiWayExplicitHierarchy<uzemnaJednotka*>();


    ds::adt::Treap<std::string, uzemnaJednotka*>* tableObce = new ds::adt::Treap<std::string, uzemnaJednotka*>();
    ds::adt::Treap<std::string, uzemnaJednotka*>* tableOkresy = new ds::adt::Treap<std::string, uzemnaJednotka*>();
    ds::adt::Treap<std::string, uzemnaJednotka*>* tableKraje = new ds::adt::Treap<std::string, uzemnaJednotka*>();
    ds::adt::Treap<std::string, uzemnaJednotka*>* tableSlovensko = new ds::adt::Treap<std::string, uzemnaJednotka*>();



    ds::adt::Treap<std::string, uzemnaJednotka*>* filterTable = tableObce;



    loader->loadObce(obce);
    loader->loadOkresy(okresy, obce);
    loader->loadKraje(kraje, okresy);
    loader->loadSlovensko(slovensko, kraje);


    loader->loadSlovenskoH(hierarchy, slovensko);
    //std::cout << hierarchy->size() << std::endl;
    loader->loadKrajeH(hierarchy, kraje);
    //std::cout << hierarchy->size() << std::endl;
    loader->loadOkresyH(hierarchy, okresy);
    //std::cout << hierarchy->size() << std::endl;
    loader->loadObceH(hierarchy, obce);
    //std::cout << hierarchy->size() << std::endl;
 //hierarchy->processLevelOrder(hierarchy->accessRoot(), [](ds::amt::MultiWayExplicitHierarchyBlock<uzemnaJednotka*>* entry) { std::cout << entry->data_->getName() << std::endl; });
 //hierarchy->processPreOrder(hierarchy->accessRoot(), [](const ds::amt::MultiWayExplicitHierarchyBlock<uzemnaJednotka*>* entry) {
 //    std::cout << entry->data_->getName() << std::endl; // Modify the lambda function to match the expected signature
 //    });
    loader->loadObceT(tableObce, obce);
    loader->loadOkresyT(tableOkresy, okresy);
    loader->loadKrajeT(tableKraje, kraje);
    loader->loadSlovenskoT(tableSlovensko, slovensko);
    


    bool end = false;
    int control = 0;
    int filterNumber = 0;
    bool stop = false;


    std::vector<uzemnaJednotka*>* temp = new std::vector<uzemnaJednotka*>();
    std::vector<ds::adt::TreapItem<std::string, uzemnaJednotka*>*>* tempTableItems = new  std::vector< ds::adt::TreapItem<std::string, uzemnaJednotka*>*>();
    //ds::amt::ImplicitSequence<uzemnaJednotka*>* temp = new ds::amt::ImplicitSequence<uzemnaJednotka*>();
    //ds::amt::ImplicitSequence<ds::adt::TreapItem<std::string, uzemnaJednotka*>*>* tempTableItems = new ds::amt::ImplicitSequence<ds::adt::TreapItem<std::string, uzemnaJednotka*>*>();
    //ds::amt::ImplicitSequence< ds::amt::MultiWayExplicitHierarchyBlock<uzemnaJednotka*>>* tempHieraryItem = new ds::amt::ImplicitSequence< ds::amt::MultiWayExplicitHierarchyBlock<uzemnaJednotka*>>();
    ds::adt::TableItem<std::string, uzemnaJednotka*>* item = nullptr;

    std::string prefix = "";
    auto node = hierarchy->accessRoot();
    auto tempNode = node->parent_;

    while (!end) {
        std::cout << "tvoje moznosti su: \n 1.vyber suboru na filtrovanie\n 2.filtrovat\n 3.hierarchia\n 4. table \n 0.end \n zadaj cislo pre pokracovanie \n ";
        std::cin >> control;
        switch (control) {
        case 1:
            std::cout << "zvolil si vyber zo suborov \n 1.obce \n 2. okresy \n 3. kraje \n";
            std::cin >> filterNumber;
            switch (filterNumber) {
            case 1:
                filterVector = obce;
                filterTable = tableObce;
                break;
            case 2:
                filterVector = okresy;
                filterTable = tableOkresy;
                break;
            case 3:
                filterVector = kraje;
                filterTable = tableKraje;
                break;
            default:
                std::cout << "invalid input";
                std::cin >> filterNumber;
                break;
            }
            break;
        case 2:
            std::cout << "zvolil si filtrovanie \n mas moznost: \n 1. pre filtrovanie startwithStr \n 2. pre filtrovanie containsStr \n";
            std::cin >> filterNumber;
            switch (filterNumber) {
            case 1:
                std::cout << "zadaj slovo na ktore ma zacinat \n";
                std::cin >> prefix;
                filter->findNameWithProperty(temp, filterVector->begin(), filterVector->end(), [&prefix](const auto& entry)
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
                filter->findNameWithProperty(temp, filterVector->begin(), filterVector->end(), [&prefix](const auto& entry)
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
        case 3:
            std::cout << "zvolil si cestovanie v hierarchii \n";
            size_t inputOrder;
            while (!stop) {
                std::cout << "aktualne si " << node->data_->getName() << std::endl << std::endl;
                std::cout << "mozes sa pohybovat hore a dole , 1-hore,2-dole,3-doprava,4-dolava \n alebo pre ukoncenie prehladavanie hierarchie - 5\n pre filtrovanie v hierarchi funkciou containsStr 6\n pre filtrovanie v hierarchii funkciou startsWithStr 7 \n 8 pre vypisanie aktualnej urovne\n";
                std::cin >> filterNumber;
                switch (filterNumber) {
                case 1:
                    tempNode = node->parent_;
                    if (node->parent_ != nullptr) {
                        node = hierarchy->accessParent(*node);
                        std::cout << "Moved up to " << node->data_->getName() << std::endl;
                    }
                    else {
                        std::cout << "You are in root \n";
                    }
                    break;
                case 2:
                    if (node->sons_ != nullptr) {
                        auto item = node->sons_->accessFirst();
                        size_t index = 0;
                        while (node->sons_->accessNext(*item)) {
                            std::cout << index << " " << item->data_->data_->getName() << std::endl;
                            item = node->sons_->accessNext(*item);
                            index++;
                        }
                        // Prompt the user to select a specific child node
                        std::cout << "Select a child node: \n";

                        std::cin >> inputOrder;
                        //pridate overenie
                        node = hierarchy->accessSon(*node, inputOrder);
                        // Implement logic to select a child node and update node accordingly
                    }
                    else {
                        std::cout << "No child nodes available \n";
                    }
                    break;
                case 3:
                    if (node->parent_ != nullptr && (hierarchy->accessParent(*node)->sons_->access(inputOrder + 1)) != nullptr) {
                        node = (hierarchy->accessParent(*node)->sons_->access(inputOrder + 1))->data_; // Update node to the next right node
                        inputOrder++;
                    }
                    else {
                        std::cout << "No right nodes available.\n";
                    }
                    break;



                case 4:
                    if (node->parent_ != nullptr && (hierarchy->accessParent(*node)->sons_->access(inputOrder - 1)) != nullptr) {
                        node = (hierarchy->accessParent(*node)->sons_->access(inputOrder - 1))->data_; // Update node to the next right node
                        inputOrder--;
                    }
                    else {
                        std::cout << "No left nodes available.\n";
                    }
                    break;
                case 5:
                    stop = true;
                    break;
                case 6://contains
                    std::cout << "zadaj slovo ktore ma obsahovat \n";
                    std::cin >> prefix;
                    hierarchy->processPreOrder(node, [&prefix, &node](const auto& entry)
                        {
                            if (entry->data_->getName() == node->data_->getName()) {
                                return false;
                            }
                    if (entry->data_->getParent() != node->data_->getName()) {
                        return false;
                    }
                    if (entry->data_->getName().length() < prefix.length()) {
                        return false;
                    }

                    if (entry->data_->getName().find(prefix) != std::string::npos) {
                        std::cout << entry->data_->getName() << std::endl;
                        return true;
                    }
                    else {
                        return false;
                    }
                        });
                    //filter->findNameWithPropertyUniversal < ds::amt::MultiWayExplicitHierarchyBlock<uzemnaJednotka*>, ds::amt::ImplicitSequence <ds::amt::MultiWayExplicitHierarchyBlock<uzemnaJednotka*>>::IteratorType, ds::amt::MultiWayExplicitHierarchyBlock<uzemnaJednotka* >> (tempHieraryItem, node->sons_->begin(), node->sons_->end(), [&prefix, &node](const auto& entry)
                    //    {
                    //        if (entry->data_->getName() == node->data_->getName()) {
                    //            return false;
                    //        }
                    //if (entry->data_->getParent() != node->data_->getName()) {
                    //    return false;
                    //}
                    //if (entry->data_->getName().length() < prefix.length()) {
                    //    return false;
                    //}

                    //if (entry->data_->getName().find(prefix) != std::string::npos) {
                    //    std::cout << entry->data_->getName() << std::endl;
                    //    return true;
                    //}
                    //else {
                    //    return false;
                    //}
                    //    });
                    break;
                case 7://start
                    std::cout << "zadaj slovo na ktore ma zacinat \n";
                    std::cin >> prefix;
                    hierarchy->processPreOrder(node, [&prefix, &node](const auto& entry)
                        {
                            if (entry->data_->getName() == node->data_->getName()) {
                                return false;
                            }
                    if ((entry->data_->getParent() != node->data_->getName() )  ) {
                        return false;
                    }

                    //if (entry..length() < prefix.length()) {
                    if (entry->data_->getName().length() < prefix.length()) {
                        return false;
                    }

                    // Check if the first prefix.length() characters of str match prefix
                    for (size_t i = 0; i < prefix.length(); ++i) {
                        if (entry->data_->getName()[i] != prefix[i]) {
                            return false;
                        }
                    }
                    std::cout << entry->data_->getName() << std::endl;
                    return true;
                        });

                    break;
                case 8:
                    hierarchy->processPreOrder(node, [&node](const auto& entry)
                        {
                            if ((entry->data_->getParent() != node->data_->getName())) {
                                return false;
                            }
                            std::cout << entry->data_->getName() << std::endl;
                        });
                    break;
                default:
                    // Handle invalid input
                    std::cout << "Invalid input \n";
                    break;
                }
            }
            break;
        case 4:
            std::cout << "zvolil si filtrovanie v tabulke \n mas moznost: \n 1. pre filtrovanie  \n";
            std::cin >> filterNumber;
            switch (filterNumber) {
            case 1:
                std::cout << "zadaj slovo na ktore ma zacinat \n";
                std::cin >> prefix;
                
                if (filterTable->tryFindTabItem(prefix,item)) {
                    std::cout << std::left << std::setw(30) << item->data_->getName() << " | "
                        << std::setw(30) << item->data_->getParent() << " | "
                        << std::setw(30) << item->data_->getCode() << "\n";
                     if (item->synonyms_.size() >= 1) {
                        for (auto i : item->synonyms_) {
                            std::cout << std::left << std::setw(30) << i->getName() << " | "
                                << std::setw(30) << i->getParent() << " | "
                                << std::setw(30) << i->getCode() << "\n";
                        }
                    }
                }
                else {
                    std::cout << "tabulka neobsahuje kluc\n";
                }
                //for (const auto& elem : *tempTableItems)
                //{
                //    std::cout << std::left << std::setw(30) << elem->data_->getName() << " | "
                //        << std::setw(30) << elem->data_->getParent() << " | "
                //        << std::setw(30) << elem->data_->getCode() << "\n";
                //}
                tempTableItems->clear();
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



    //vectors
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
    delete kraje;
    for (auto& item : *slovensko) {
        delete item;
    }
    delete slovensko;

    //hierarchy
    delete hierarchy;

    //table
    delete tableObce;
    delete tableKraje;
    delete tableOkresy;
    delete tableSlovensko;



    delete temp;
    delete tempTableItems;
    //delete tempHieraryItem;


    delete filter;
    delete loader;



    //std::cout << "Hello World!";
    return 0;
}