#include "company.h"
#include "jaro.h"

Company::Company() {
    this->id = "0x";
}

Company::Company(std::string name) {
    this->companyName = name;
    this->list.push_back(name);
    // this->id =
}

bool Company::isSimilar(std::string name) {
    double dist = jaroWinklerDistance(name, this->companyName);
    return (dist >= .9) ? true : false;                                 // CHANGE THIS NUMBER TO AFFECT ACCURACEY
}

void Company::addAlias(std::string alias) {
    this->list.push_back(alias);
}