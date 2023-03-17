#include "company.h"
#include "jaro.h"

std::string Company::generateId(const std::string firstCompany, const unsigned id) {
    std::string firstTwoLetters = "";
    int validCharCount = 0;
    int i = 0;
    while (validCharCount < 2) {            // id format is AA10000, first two valid chars from the company, then its number id assigned in misc.cpp
        if (firstCompany[i] > 64 && firstCompany[i] < 91) { // make sure its a capital letter
            firstTwoLetters += firstCompany[i];
            validCharCount++;
        }
        i++;
    }
    return std::string( (firstTwoLetters + std::to_string(id)) );  // id is a string
}

Company::Company(std::string name, unsigned id)
: companyName(name), id(generateId(name, id))       // sets the private const variables
 {
    this->list.push_back(name);   
}

bool Company::isSimilar(const std::string& name) {
    double dist = jaroWinklerDistance(name, this->companyName);
    return (dist >= .9) ? true : false;                                 // CHANGE THIS NUMBER TO AFFECT ACCURACEY
}

void Company::addAlias(std::string alias) {
    this->list.push_back(alias);
}