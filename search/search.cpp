#include "search.h"
#include <fstream>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdlib.h>
/*The searchWord feature only works on windows because of the shellExecute function
 * But you can implement it by yourself for macOS or Linux
 * It basically opens a string in your browser.
 */
void searchWord() {
    std::cout << "What are you looking for?\n";
    std::string word, search, base_url2, search2;
    const std::string base_url = "www.dictionary.com/browse/";
    base_url2 = "https://en.wikipedia.org/wiki/";
    std::cin >> word;
    search = base_url + word;
    search2 = base_url2 + word;
    /*change chromium to your default browser
     *to open both tabs
     * */
    system(("chromium -new-tab " + search).c_str());
    system(("chromium -new-tab " + search2).c_str());
    checkWord(word);
    runPy(word);
    /*If you are using this on Windows you should uncomment the ShellExecute function
     */
    //ShellExecute(0, _T("open"), search.c_str(), 0, 0, 0);
    //ShellExecute(0, _T("open"), search2.c_str(), 0, 0, 0);

};

/*The function only scans whether the searched is already in the file
 * or not. If it is not, the name of the word will be appended.
 */
void checkWord(const std::string& the_word) {
    std::string filepath = {"../search/history.txt"}; //Saves all the searched words
    std::ifstream ifs(filepath); 
    if(ifs.is_open()) {
        bool isInFile = false; //true if the the word is already in the file
        std::string line;
        while(std::getline(ifs, line)) {
            //transform the first charater of the line to lowercase
            std::transform(line.begin(), line.end(),line.begin(), [](unsigned char c)
                    {return std::tolower(c);});
            if (the_word == line){
                isInFile = true;
            }
        }
        //If the isInFile is not true, it will append the word
        if (!isInFile) {
            std::cout << "It is not in file and will be added!\n";
            std::ofstream ofs(filepath,std::ofstream::app);
            ofs << the_word << std::endl;
            ofs.close(); 
        }
        ifs.close();
    } else {
        std::cerr << "Cannot open the file" << std::endl;
    }
}
//It will run the python script with the searched wordas a command line argument
void runPy(std::string &searched_word) {
    std::string command = "python3 ../voice/scraping.py " + searched_word;
    system(command.c_str());
}
