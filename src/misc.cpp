#include "misc.h"
#include "jaro.h"
#include <fstream>

bool strAreLogicallyEq(const std::string& company1, const std::string& company2) {
    double dist = jaroWinklerDistance(company1, company2);
    return (dist >= .9936) ? true : false;                                 // CHANGE THIS NUMBER TO AFFECT ACCURACEY (found that this number is best when testing)
}

std::vector<Company> buildSortedCompanies(const set_vec &lists) {
    std::vector<Company> allCompanies;
    for (str_s list: lists) {               // loop through the vector, access each list
        for (std::string name : list) {     // loop through the list, find respective company and add (or create new)
            if (allCompanies.empty()) {
                allCompanies.push_back(Company(name));
                continue;
            }
            for (Company &c: allCompanies) {
                if (allCompanies.back() == c) {         // this if statement will trigger if no matching company is found (we reached the last element in the vector)
                    if (c.isSimilar(name)) {                   // check if its similar to the last element
                        c.addAlias(name);                      // if so, add alias to the company
                    }
                    else {
                        allCompanies.push_back(Company(name)); // no companies match this company, create a new one 
                    }
                }
                else {
                    if (c.isSimilar(name))                      // create new company if no simliar companies are found
                        c.addAlias(name);
                }
            }
            // q.pop();
        }
    }
    return allCompanies;
}

str_s getPastDataSet() {
    str_s pastData;
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
            pastData.insert(line);
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