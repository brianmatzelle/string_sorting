#ifndef COMPANY_H_
#define COMPANY_H_
#include <string>
#include <vector>
#include <iostream>

class Company {

public:
    Company();
    Company(std::string name);
    Company(const std::string& name, const unsigned& id);
    bool isSimilar(std::string name);
    bool operator==(const Company& rhs) { return (this->companyName == rhs.companyName) ? true : false; };
    void addAlias(std::string alias);
    inline friend std::ostream& operator<<(std::ostream &os, const Company &c) {
        os << 
        c.id <<
        "-";
        for (unsigned i = 0; i < c.list.size(); i++) {
            os << c.list[i];
            if (i < c.list.size()-1) 
                os << " # ";                      // SEPARATER BETWEEN COMPANIES
        }
        os << "-";
        return os;
    }

private:
    std::string companyName;
    std::vector<std::string> list;
    std::string id;                 // id = first 2 letters from list[0] + id_num
    unsigned id_num;
};


#endif