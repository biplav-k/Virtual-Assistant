#include "deck.h"
#include <memory>
#include <random>
#include <filesystem>
#include <fstream>

/* *How the algorithm create the decks of .txt files works*
 *
 * The algorithm only works if a line has a question mark(?) at the end
 * and nothing before and only a new line ("\n") after it.
 * Basically it checks each non-empty line of a .txt file.
 * If the line ends with a "?" it saves it as a key of a std::pair data structure
 * Each of the following lines without a "?" 
 * will be appended as the value to the previous question.
 * This will continue as long as the loop finds another line with a "?".
 * In the decks/ directory there is an example.txt file which,
 * demonstrates exactly how a file has to be structured. 
 *
 */
void Deck::create_deck(std::string &file)
{
    //BUG I have to remove the whitespaces from the line especially if one occurs right after
    //the question mark of the question. It causes a segmentation fault and exits the program
    std::ifstream ifs(file);
    if(ifs.is_open()) {
        std::shared_ptr<Card> card = std::make_shared<Card>();
        int counter = 0;
        std::string line, last_question;
        while(getline(ifs, line)) {
            if (line.back() == '?' || line.front() == '#'){ //Checks the last character of the line 
                std::shared_ptr<Card> card = std::make_shared<Card>();
                //to check increment after the first pair was completely added
                if(!_deck.empty())
                    ++counter;
                _deck.push_back(*card);
                _deck[counter].info.first = line;
                last_question = line;
            } else if (line.size()>3){
                _deck[counter].info.second = _deck[counter].info.second + "\n" + line;
            }
        }
    } else {
        std::cerr << "Cannot open the file \n";
    }
};

int generateRandomNumber(const std::vector<Card> &item) {
    std::random_device random_dev;
    std::mt19937 gen(random_dev());
    std::uniform_int_distribution<> distr(0, item.size()-1);    
    int random_num = distr(gen);
    return random_num;
};

/*
 * The startSession method will start a session. The limit parameter sets the goal for correct guesses for each card
 * It will pick random cards, will wait until you pressed a character to show you the answer
 * If your guess was correct you shold type 'y' and it will automatically increment the number of correct guesses
 * If a card has reached the limit of correct guesses, it will be removed from the temporary list
 * The user can exit if he presses 'q'
 */

void Deck::startSession(int limit) 
{ //if one card has reached the limit, it wont be displayed anymore
    std::vector<Card>temp_deck = _deck;
    std::string delay;
    std::string answer;
    while(!temp_deck.empty()) {
        //Will generate a random number for each iteration in the range of the deck size
        int randNum = generateRandomNumber(temp_deck);
        std::cout << "\n * Question * \n " << temp_deck[randNum].getCard().first;
        std::cout << "\n Type in any character to show the answer: ";
        std::cin >> delay;
        std::cout << "\n * Answer * " << temp_deck[randNum].getCard().second << "\n";
        std::cout << "\nCorrect(y), Wrong(n): ";
        std::cin >> answer;
        std::cout << "\n\n\n\n";
        if(answer == "y") {
            temp_deck[randNum].incrementCorrect();
            if (temp_deck[randNum].correct == 4){
                //Get the first element to add the index of the element that has to be removed if it reaches the limit
                auto it = temp_deck.begin(); 
                temp_deck.erase(temp_deck.begin() +randNum);
            }
        }
        if (delay == "q")//Press "q" to quit the current session
            break;
    }
};

void Deck::printDeck() {
    for (const auto &card: _deck) {
        std::cout << card.info.first << " : " << card.info.second << "\n";
    }
};

/* Displays all files in the decks/ directory and their associated index
 * Can pick a file by typing in the index
 */
std::string choose_deck() {
    //Stores all the directory entries
    std::vector<std::filesystem::directory_entry> entries;
    int choice, indexNum = 0;
    std::cout << "These are the available decks: \n";
    //Displays all the available decks
    for (const auto &entry: std::filesystem::directory_iterator("../files/decks")){
        entries.push_back(entry);
        std::cout << indexNum << ") " << entry.path().filename().string() << std::endl;
        ++indexNum;
    }
    std::cout << "Pick the number of the deck \n";
    std::cin >> choice;
    if (choice < entries.size())
        std::cout << "You've choosed: " << entries[choice].path().filename().string() << "\n ==========================================\n";
    else{
       std::cout << "Number is out of range, try again!\n";
       choose_deck(); 
}
    return entries[choice].path().string();
}
//TODO create a function that creates checks if a "decks/" directory is available and if not, the function creates one
void create_new_deck() {
    const std::string decks_dir= "../files/decks/";
    bool exists = false;
    std::cout << "What is the name of the Deck?" << std::endl;
    std::string deck_name;
    std::cin >> deck_name;
    std::string file = deck_name + ".txt";
    //Before creating the file, check if its already in the deck
    for (const auto &entry: std::filesystem::directory_iterator("../files/decks")){
        if ((decks_dir+file) == entry.path().string())
            exists = true;
    }
        if (!exists) {
            std::ofstream filename(decks_dir + file);
            filename.close();
            std::cout << "Deck was created\n";
        } else 
            std::cout << "File already exists\n";
    }

