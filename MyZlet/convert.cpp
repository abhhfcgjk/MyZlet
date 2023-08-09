#include "convert.h"
#define DEBUG

extern std::string tmpFileName;

std::string convertCommand(std::string line, std::string com) {
    using namespace std;
    string tmp("A", line.size() - com.size() - 1);
    for (int i = 0; i < tmp.size(); i++) {
        tmp[i] = line[i + com.size() - 1];
    }
    return tmp;
}

std::string getText() {
    char c;
    std::string text;
    while (std::cin.get(c) && c != '\n' && c != EOF)
        text.push_back(c);

    return text;
}

std::string getByNumberAll(unsigned number, std::string file) {
    if (number <= 0) throw crd::CardException("Uncorrect line's number.", crd::arguments);
    std::ifstream openedFile(file, std::ios_base::in);
    std::string line;
    unsigned counter = 0;
    if (openedFile.is_open())
        while (std::getline(openedFile, line) && (++counter != number)) {}
    else {
        throw crd::CardException("This group doesn't exist.", crd::arguments);
    }
    openedFile.close();
    if (counter == number) return line;
    throw crd::CardException("Uncorrect number.", crd::arguments);
}

std::string getByNumberName(unsigned number, std::string file) {
    std::string line = getByNumberAll(number, file);
    unsigned char i = 0;
    while(line[i++] != '-'){}
    std::string cardName;
    if(i >= 2)
        cardName.assign(line, 0, i-2);
    return cardName;
}

std::vector<std::string> getCommand() {
    char c;
    std::vector<std::string> splitted_command{};
    std::string str;
    while (std::cin.get(c)) {
        if(c != ' ' && c!='\n' && c != EOF)
            str.push_back(c);
        if (c == '\n' || c == EOF || c==' ') {
            if(!str.empty())
                splitted_command.push_back(str);
            if(c=='\n' || c == EOF)
                return splitted_command;
            else
                str = "";
        }
    }
    return splitted_command;
}


unsigned convertToNumber(std::string& str) {
    unsigned numb = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] < '0' || str[i] > '9') throw crd::CardException("Uncorrect number.", crd::arguments);
        numb = numb * 10 + (str[i] - '0');
    }
    return numb;
}


void deleter(unsigned _Number, const std::string& openedGroup) {
    std::string line;
    std::ifstream fileWords(openedGroup, std::ios_base::in);
    std::ofstream tmp(tmpFileName, std::ios_base::out);
    unsigned number = 1;
    bool flag = false;
    if (fileWords.is_open())
        while (std::getline(fileWords, line)) {
            flag = (_Number == number);
            if (_Number != number) {
                tmp << line << std::endl;
            }
            number++;
        }
    else {
        throw crd::CardException("", crd::arguments);
    }
    if (!flag) {
        throw crd::CardException("Uncorrect number.", crd::arguments);
    }
    tmp.close();
    fileWords.close();
    std::ofstream fileWords2(openedGroup, std::ios_base::out);
    std::ifstream tmp2(tmpFileName, std::ios_base::in);
    if (tmp2.is_open())
        while (std::getline(tmp2, line)) {
            fileWords2 << line << std::endl;
        }
    else {
        throw crd::CardException("Error", crd::command);
    }
    tmp2.close();
    fileWords2.close();
}