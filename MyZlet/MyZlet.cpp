#include <iostream>
#include "CardExceptions.h"
#include "Card.h"
#include <vector>
#include "convert.h"

//#define DEBUG
std::string tmpFileName = "tmp.txt";
const char* filegroups = "groups.txt";
const char* help = "help.txt";

bool isGroupExist(std::string&);
void printConverter(std::vector<std::string>&, std::string& groupFileName);

int main()
{
    Group openedGroup;
    while (true) {
        std::string groupFileName = openedGroup.GetFileName();
        std::cout << openedGroup.GetName() << ">";
        std::vector<std::string> command = getCommand();

        if (command[0] == "quit" && command.size() == 1) return 0;
        else if (command[0] == "help") {
            std::ifstream fileHelp(help, std::ios_base::in);
            printAll(help);
            fileHelp.close();
        }
        else if (command[0] == "ng" && command.size() == 2) { //Create new group of cards
            std::string groupName = command[1];
            openedGroup.SetGroup(groupName);
            std::ofstream groups(filegroups, std::ios_base::app);
            groups << groupName << std::endl;
            groups.close();
        }
        else if (command[0] == "cd.." || (command.size()==2 && command[0] == "cd" && command[1] == "..")) {
            openedGroup.SetGroup("");
        }
        else if (command[0] == "cd" && command.size() <= 2) {
            if (isGroupExist(command[1])) {
                openedGroup.SetGroup(command[1]);
            }
            else {
                std::cout << "This group doesn't exist." << std::endl;
            }
        }
        else if (command[0] == "nc") { //Create new card in currently opened group
            std::string name;
            if (command.size() < 2) {
                std::cout << "Enter the card name" << std::endl;
                continue;
            }
            for (int i = 1; i < command.size(); i++)
                name += command[i] + " ";
            name.pop_back();
            std::cout << "Enter text: " << std::endl;
            std::string text = getText();

            Card card(name, text);
            
            saveCard(card, groupFileName);
        }
        else if (command[0] == "print") { // print -key <selectedGroupName>
            try {
                printConverter(command, groupFileName);
            }
            catch (const crd::CardException& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if (command[0] == "rm" && command.size() == 3) {
            try {
                delGroupCard(openedGroup.GetFileName(), command[1], command[2]);
            }
            catch (const crd::CardException& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else {
            if (!command[0].empty())
                std::cout << "commant uncorrect" << std::endl;
        }
    }
    return 0;
}



void printConverter(std::vector<std::string>& command, std::string& groupFileName) {
    if ((command.size() == 1) && groupFileName.empty()) {
        printAll(filegroups);
    }
    else if ((command.size() == 1) && !groupFileName.empty()) {
        printAll(groupFileName);
    }
    else if (groupFileName.empty() && (command.size() == 3)) {
#ifdef DEBUG
        std::cout << "First if: printGroup" << std::endl;
#endif
        std::string tmp = command[2] + ".txt";
        printGroup(tmp, command[1]);
#ifdef DEBUG
        std::cout << "First if: printGroup" << std::endl;
#endif
    }
    else if (groupFileName.empty() && (command.size() == 4)) {
#ifdef DEBUG
        std::cout << "second if: printByNumber" << std::endl;
#endif
        std::string tmp = command[2] + ".txt";
        printByNumber(tmp, command[1], command[3]);
    }
    else if (!groupFileName.empty() && (command.size() == 3)) {
#ifdef DEBUG
        std::cout << "therd if: " << std::endl;
        std::cout << groupFileName << std::endl;
#endif
        if (command[1].find('g') != command[1].npos) printGroup(groupFileName, command[1]);
        else printByNumber(groupFileName, command[1], command[2]);
    }
    else {
        throw crd::CardException("Use help.", crd::command);
    }
}

bool isGroupExist(std::string& inputFile){
    std::ifstream file(inputFile+".txt", std::ios_base::in);
    bool ans = file.is_open();
    if (ans) {
        file.close();
        return ans;
    }
    return ans;
}
