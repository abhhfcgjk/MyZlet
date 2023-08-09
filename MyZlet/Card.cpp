#include "Card.h"
#include "CardExceptions.h"

//#define DEBUG

extern const char* filegroups;

void saveCard(Card& card, std::string& openedGroupFile) {
    std::ofstream fileWords(openedGroupFile, std::ios_base::app);
    fileWords << card.name + " - " + card.text + ".\n";
    fileWords.close();
}

void Card::print() {
    std::cout << name << " - " << text << std::endl;
}
std::string Group::GetName() {
    return this->groupName;
}
std::string Group::GetFileName() {
    if (groupName.empty()) return "";
    return groupName + ".txt";
}

void Group::print() {
    printAll(groupName);
}

void printGroup(std::string& command, std::string& key) {
    void (*printer) (std::string);
    if (key == "-g")
        printer = printAll;
    else if (key == "-gh")
        printer = printNames;
    else if (key.empty()) {
        std::cout << key;
        printAll(filegroups);
        return;
    }
    else
        throw crd::CardException("Uncorrect key", crd::key);

    try {
        if (!command.empty()) {
            printer(command);
        }
    }
    catch (const crd::CardException& error) {
        std::cout << "runtime error: " << error.what() << std::endl;
    }
    
}

void printByNumber(std::string& command, std::string& key, std::string& num) {// print cards by selected number
    int number{};
    try {
        number = convertToNumber(num);// convert argument from string to unsigned
    }
    catch (crd::CardException& ex) {
        std::cout << ex.what() << std::endl;
        return;
    }
    std::string (*card) (unsigned, std::string);

    if (key == "-n") //if input "print -n" just output selected card
        card = getByNumberAll;
    else if (key == "-nh") //if input "print -nh" output card's title 
        card = getByNumberName;
    else
        throw crd::CardException("Uncorrect key.", crd::key);

    try {
        if (!command.empty())
            std::cout << card(number, command) << std::endl;
#ifdef DEBUG
        std::cout << "Card printed correct" << std::endl;
#endif
    }
    catch (const crd::CardException& error) {
        std::cout << "runtime error: " << error.what() << std::endl;
    }
}


void delGroupCard(const std::string& fileName, std::string& key, std::string& number) {
    if(fileName.empty() && (key == "-g")) {
        unsigned num = convertToNumber(number);
        deleter(num, filegroups);
    }
    else if (!fileName.empty() && (key == "-n")) {
        unsigned num = convertToNumber(number);
        deleter(num, fileName);
    }
    else if (!fileName.empty() && (key == "-g")) {
        throw crd::CardException("Use help.", crd::command);
    }
    else if (fileName.empty() && (key == "-n")) {
        throw crd::CardException("Use help.", crd::command);
    }
    else {
        throw crd::CardException("Uncorrect key.", crd::key);
    }
}
