#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include "jaro.h"
#include "company.h"

int main() {
    std::ifstream parsedFile;
    std::ofstream sortedOutput;
    std::string path = "python_output.txt";
    parsedFile.open(path);
    std::queue<std::string> list_1;
    std::queue<std::string> list_2;
    bool addToList1 = true;
    if (parsedFile.fail()) {
        std::cout << "ERROR: could not open " << path << " ... does this file exist?" << std::endl;
    }
    else {
        while (!parsedFile.eof()) {
            std::string str;
            getline(parsedFile, str);
            if (str == "LIST_2:")
                addToList1 = false;
            if (addToList1)
                list_1.push(str);
            else {
                list_2.push(str);
            }
        }
    }
    
    std::vector<Company> allCompanies;
    list_1.pop();                       // pop list 1 tags
    list_1.pop();
    while (!list_1.empty()) {
        std::string name = list_1.front();
        if (allCompanies.empty()) {
            allCompanies.push_back(Company(name));
            continue;
        }
        for (Company &c: allCompanies) {
            if (allCompanies.back() == c) {
                if (!c.isSimilar(name)) {
                    allCompanies.push_back(Company(name));
                }
                else {
                    c.addAlias(name);
                }
            }
            else {
                if (c.isSimilar(name))
                    c.addAlias(name);
            }
        }
        list_1.pop();
    }

    list_2.pop();                       // pop list 2 tags
    list_2.pop();
    while (!list_2.empty()) {
        std::string name = list_2.front();
        if (allCompanies.empty()) {
            allCompanies.push_back(Company(name));
            continue;
        }
        for (Company &c: allCompanies) {
            if (allCompanies.back() == c) {
                if (!c.isSimilar(name)) {
                    allCompanies.push_back(Company(name));
                }
                else {
                    c.addAlias(name);
                }
            }
            else {
                if (c.isSimilar(name))
                    c.addAlias(name);
            }
        }
        list_2.pop();
    }

    sortedOutput.open("sorted_companies.txt");
    if (sortedOutput.is_open()) {
        for (Company c: allCompanies)
            sortedOutput << c << "\n";
        sortedOutput.close();
    }
}