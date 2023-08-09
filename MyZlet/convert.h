#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "CardExceptions.h"

std::string convertCommand(std::string, std::string);
std::vector<std::string> getCommand();
unsigned convertToNumber(std::string&);
std::string getText();
std::string getByNumberAll(unsigned, std::string);
std::string getByNumberName(unsigned, std::string);
void deleter(unsigned, const std::string&);

template<class T>
void printAll(T file) {
    std::string line;
    std::ifstream openedFile(file, std::ios_base::in);
    unsigned number = 1;
    if (openedFile.is_open())
        while (std::getline(openedFile, line)) {
            std::cout << number << ") " << line << std::endl;
            number++;
        }
    else {
        throw crd::CardException("This group doesn't exist.", crd::arguments);
    }
    openedFile.close();
}

template<class V>
void printNames(V file) {
    std::string line;
    std::ifstream openedFile(file, std::ios_base::in);
    unsigned number = 1;
    if (openedFile.is_open())
        while (std::getline(openedFile, line)) {
            unsigned char i{};
            while (line[i++] != '-') {}
            std::string cardName;
            cardName.assign(line,0, i-2);

            std::cout << number << ") " << cardName << std::endl;
            number++;
        }
    else {
        throw crd::CardException("This group doesn't exist.", crd::arguments);
    }
    openedFile.close();
}

