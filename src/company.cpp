#include "company.h"
#include "jaro.h"

Company::Company() {
    this->id = "0";
    this->id_num = 0;
    this->companyName = "NULL";
}

Company::Company(std::string name) {
    this->id = "0";
    this->id_num = 0;
    this->companyName = name;
    this->list.push_back(name);
}

Company::Company(const std::string& name, const unsigned& id) {
    this->companyName = name;
    this->list.push_back(name);
    this->id_num = id;
    std::string firstTwoLetters = "";
    int validCharCount = 0;
    int i = 0;
    while (validCharCount < 2) {            // id format is AA10000, first two valid chars from the company, then its number id assigned in misc.cpp
        if (name[i] > 64 && name[i] < 91) { // make sure its a capital letter
            firstTwoLetters += name[i];
            validCharCount++;
        }
        i++;
    }
    this->id = firstTwoLetters + std::to_string(this->id_num);  // id is a string
}

bool Company::isSimilar(std::string name) {
    double dist = jaroWinklerDistance(name, this->companyName);
    return (dist >= .9) ? true : false;                                 // CHANGE THIS NUMBER TO AFFECT ACCURACEY
}

void Company::addAlias(std::string alias) {
    this->list.push_back(alias);
}