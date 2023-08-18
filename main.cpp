#include <filesystem>
#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <stdlib.h>
#include "deck/deck.h"
#include "search/search.h"
namespace fs = std::filesystem;


int main() {
    std::cout << "1. Search \n2. Learn \n";
    int choice;
    std::cin >> choice;
    if (choice == 1)
        searchWord();
    else if(choice == 2) { 
        std::string the_deck = choose_deck();
        std::string file {the_deck};
        std::shared_ptr<Deck> firstdeck = std::make_shared<Deck>(file);
        firstdeck->startSession(2);
    }
}
