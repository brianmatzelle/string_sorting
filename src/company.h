#ifndef COMPANY_H_
#define COMPANY_H_
#include <string>
#include <vector>
#include <iostream>

class Company {

public:
    Company(std::string name, unsigned id);     // only constructor becuase a compnany should never be initialized without a name or id, since we have constant private variables
    bool isSimilar(const std::string& name);
    inline bool operator==(const Company& rhs) const { return (this->companyName == rhs.companyName) ? true : false; };
    void addAlias(const std::string alias);
    inline friend std::ostream& operator<<(std::ostream &os, const Company &c) {
        os << 
        c.id <<
        "-";
        for (unsigned i = 0; i < c.list.size(); i++) {
            os << c.list[i];
            if (i < c.list.size()-1) 
                os << " # ";                      // DELIMITER BETWEEN COMPANIES
        }
        os << "-";
        return os;
    }

private:
    const std::string companyName;
    const std::string id;                 // id = first 2 letters from list[0] + id_num
    std::vector<std::string> list;
    std::string generateId(const std::string firstCompany, const unsigned id_num);
};


#endif