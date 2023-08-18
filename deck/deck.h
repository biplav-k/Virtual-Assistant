#ifndef DECK_H
#define DECK_H

#include <vector>
#include <fstream>
#include <iostream>
#include <tuple>
/*
 * A Deck contains several Cards. 
 * Each Card consists of an info member which stores
 * the question and answers as a std::pair<string, string>
 */
class Card {
    public:
        Card() = default;
        std::pair<std::string, std::string> info; //Question and Answer
        int correct = 0; //Number of correct answers in a session. Default is set to 0.
        std::pair<std::string, std::string> &getCard() {return info;}
        void incrementCorrect() {++correct;} //Increment the correct member if the guess was correct
};
class Deck{
    public:
        void create_deck(std::string &file);//Creates a deck of the given file
        Deck(std::string &filename)
            :_filename{filename} {
                create_deck(filename);
            }
        std::vector<Card> &get_deck () {return _deck;}
        void printDeck(); //Displays all the Cards of a deck
        //Starts a session. The param "limit" sets the goal of correct answers for each card. 
        void startSession(int limit);
            
    private:
        std::vector<Card> _deck;
        std::string _filename;
};

std::string choose_deck();

#endif
