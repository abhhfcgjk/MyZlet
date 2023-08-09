#pragma once
#include "convert.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

void printGroup(std::string& command, std::string& key);
void printByNumber(std::string& command, std::string& key, std::string& number);
void delGroupCard(const std::string& fileName, std::string& key, std::string& number);

class Card {
    friend void saveCard(Card&, std::string&);
private:
    std::string name;
    std::string text;
    std::string tag;
public:
    Card() = default;
    Card(const Card&) = delete;
    Card(const Card&&) = delete;
    Card(std::string _name) : name(_name), text(""), tag("") {}
    Card(std::string _name, std::string _text) : name(_name), text(_text), tag("") {}
    Card(std::string _name, std::string _text, std::string _tag) : name(_name), text(_text), tag(_tag) {}
    void print();
};

void saveCard(Card&, std::string&);


class Group {
private:
    std::string groupName;
public:
    Group() = default;
    Group(std::string name) : groupName(name){}
    std::string GetName();
    std::string GetFileName();
    void print();

    template <class V>
    void SetGroup(V& param) {
        this->groupName = param;
    }
};
