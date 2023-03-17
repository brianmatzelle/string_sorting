#include "company.h"
#include "jaro.h"

Company::Company() {
    this->id = "0x";
}

Company::Company(std::string name) {
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
    while (validCharCount < 2) {
        if (name[i] > 64 && name[i] < 91) {
            firstTwoLetters += name[i];
            validCharCount++;
        }
        i++;
    }
    this->id = firstTwoLetters + std::to_string(this->id_num);
}

bool Company::isSimilar(std::string name) {
    double dist = jaroWinklerDistance(name, this->companyName);
    return (dist >= .9) ? true : false;                                 // CHANGE THIS NUMBER TO AFFECT ACCURACEY
}

void Company::addAlias(std::string alias) {
    this->list.push_back(alias);
}