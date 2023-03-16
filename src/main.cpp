#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include "jaro.h"
#include "company.h"
#include <map>

int main(int argc, char *argv[]) {
    // THIS PROGRAM MUST BE RUN FROM THE ROOT DIRECTORY, OTHERWISE FILE STREAMS WON'T OPEN CORRECTLY

    std::vector<Company> allCompanies;
    typedef std::queue<std::string> str_q;      // each list is stored in a queue
    typedef std::vector<str_q> q_vec;           // the lists (queues) are then stored in a vector
    q_vec q_vector;

    // if (argc != 2) {
    //     std::cout <<  "Error, program format is: bin/main <list_count>" << std::endl;
    //     return 0;
    // }
    // int list_count = std::stoi(argv[1]);

    if (argc > 1) {
        std::cout << "ERROR: no arguments needed for this program." << std::endl;
        return 0;
    }
    int list_count = 2;     // is this always true? same line in python file
    for (int i = 0; i < list_count; i++) {
        q_vector.push_back(str_q());
    }

    std::ifstream parsedFile;
    std::ofstream sortedOutput;
    std::string path = "interim/sheet_contents.txt";
    parsedFile.open(path);          // file from python program, contains companies as strings

    int list_i = 0;                // to keep track of which list we're on, so we know which queue to add the company string to
    if (parsedFile.fail()) {
        std::cout << "ERROR: could not open \"" << path << "\", does this file exist?" << std::endl;
        return 0;
    }
    while (!parsedFile.eof()) {
        std::string str;
        getline(parsedFile, str);
        if (str == "") {                // this counter only works because of the formatting of sheet_contents.txt (it starts with \n and has a \n after every list)
            list_i++;
            continue;
        }
        q_vector[list_i].push(str);     // add the company string to its list's queue
    }

    for (str_q q: q_vector) {           // loop through the vector, access each list
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

    sortedOutput.open("interim/sorted_companies.txt");
    if (sortedOutput.is_open()) {
        for (Company c: allCompanies)
            sortedOutput << c << "\n";
        sortedOutput.close();
    }
}