#ifndef COMPANY_H_
#define COMPANY_H_
#include <string>
#include <vector>
#include <iostream>

class Company {

public:
    Company();
    Company(std::string name);
    bool isSimilar(std::string name);
    bool operator==(const Company& rhs) { return (this->companyName == rhs.companyName) ? true : false; };
    void addAlias(std::string alias);
    inline friend std::ostream& operator<<(std::ostream &os, const Company &c) {
        os << "Company [ ";
        for (unsigned i = 0; i < c.list.size(); i++)
            os << c.list[i] << ", ";
        os << " ]";
        return os;
    }

private:
    std::string companyName;
    std::vector<std::string> list;
    std::string id;
};


#endif