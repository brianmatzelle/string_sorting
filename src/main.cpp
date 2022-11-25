#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include "jaro.h"
#include "company.h"

int main(int argc, char *argv[]) {
    // argv[1] will be the number of

    std::vector<Company> allCompanies;

    typedef std::queue<std::string> str_q;
    typedef std::vector<str_q> q_vec;
    q_vec q_vector;


    std::ifstream parsedFile;
    std::ofstream sortedOutput;
    std::string path = "interim/sheet_contents.txt";
    parsedFile.open(path);

    for (int i = 0; i < std::stoi(argv[1]); i++) {
        q_vector.push_back(str_q());
    }
    int list_counter = -1;
    if (parsedFile.fail()) {
        std::cout << "ERROR: could not open " << path << " ... does this file exist?" << std::endl;
    }
    else {
        while (!parsedFile.eof()) {
            std::string str;
            getline(parsedFile, str);
            if (str == "") {
                list_counter++;
                continue;
            }
            q_vector[list_counter].push(str);
        }
    }

    for (str_q q: q_vector) {
        q.pop();
        q.pop();
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

    sortedOutput.open("interim/sorted_companies.txt");
    if (sortedOutput.is_open()) {
        for (Company c: allCompanies)
            sortedOutput << c << "\n";
        sortedOutput.close();
    }
}