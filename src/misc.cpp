#include "misc.h"
#include "jaro.h"
#include <fstream>

bool strAreLogicallyEq(const std::string& company1, const std::string& company2) {
    double dist = jaroWinklerDistance(company1, company2);
    return (dist >= .98) ? true : false;                                 // CHANGE THIS NUMBER TO AFFECT ACCURACEY
}

std::vector<Company> buildSortedCompanies(q_vec &lists) {
    std::vector<Company> allCompanies;
    for (str_q q: lists) {               // loop through the vector, access each list
        // q.pop();                     // not sure why these pop()s are here, they might be wrong. not deleting in case a bug is found
        // q.pop();
        while (!q.empty()) {
            std::string name = q.front();
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
            q.pop();
        }
    }
    return allCompanies;
}

str_q getPastDataQ() {
    str_q pastData;
    std::ifstream infile;
    std::string path = "data/past_companies.txt";
    infile.open(path);

    int id_num = 10000;
    if (infile.fail()) {
        std::cout << "ERROR: could not open \"" << path << "\", does this file exist?" << std::endl;
        exit(0);
    }
    while (!infile.eof()) {
        std::string line;
        getline(infile, line);
        if (line != "") {
            pastData.push(line);
            id_num++;
        }
    }
    return pastData;
}

std::vector<std::string> getPastDataVec() {
    std::vector<std::string> pastData;
    std::ifstream infile;
    std::string path = "data/past_companies.txt";
    infile.open(path);

    int id_num = 10000;
    if (infile.fail()) {
        std::cout << "ERROR: could not open \"" << path << "\", does this file exist?" << std::endl;
        exit(0);
    }
    while (!infile.eof()) {
        std::string line;
        getline(infile, line);
        if (line != "") {
            pastData.push_back(line);
            id_num++;
        }
    }
    return pastData;
}

bool alreadyExists(const std::vector<std::string>& pastData, const std::string& company) {
    for (std::string str : pastData) {
        if (strAreLogicallyEq(str, company))
            return true;
    }
    return false;
}

void printPastData(const std::vector<std::string>& pastData) {
    std::ofstream outfile;
    outfile.open("data/test.txt");
    for (std::string str : pastData) {
        outfile << str << std::endl;
    }
    outfile.close();
}