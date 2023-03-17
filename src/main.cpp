#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include "jaro.h"
#include "company.h"
#include "misc.h"
#include <set>

int main() {
    // THIS PROGRAM MUST BE RUN FROM THE ROOT DIRECTORY, OTHERWISE FILE STREAMS WON'T OPEN CORRECTLY

    /* INITIATE LISTS */
    Lists lists;    // Lists defined in misc.h (vec of string lists)

        /* GET PAST DATA (pseudo database) */
        std::vector<std::string> pastDataVec = getPastDataVec();
        lists.push_back(pastDataVec);       // pastDataVec needs to be added first to maintain proper IDs
        /* GET PAST DATA (pseudo database) */

    int list_count = 2;     // is this always true? same line in python file
    for (int i = 0; i < list_count; i++) {
        lists.push_back(str_v());           // each list is a set, the sets are then stored in this var
    }
    /* INITIATE LISTS */

    /* PARSE THROUGH PYTHON GENERATED LIST */
    std::ifstream parsedFile;
    std::string path = "interim/sheet_contents.txt";
    parsedFile.open(path);          // file from python program, contains companies as strings
    int list_i = 0;                // to keep track of which list we're on, so we know which queue to add the company string to
    if (parsedFile.fail()) {
        std::cout << "ERROR: could not open \"" << path << "\", does this file exist?" << std::endl;
        return 0;
    }
    while (!parsedFile.eof()) {
        std::string line;
        getline(parsedFile, line);
        if (line == "") {                // this counter only works because of the formatting of sheet_contents.txt (it starts with \n and has a \n after every list)
            list_i++;
            continue;
        }
        else if ( !alreadyExists(pastDataVec, line) ) {
            pastDataVec.push_back(line);
            lists[list_i].push_back(line);
        }
        else
            continue;
    }
    /* PARSE THROUGH PYTHON GENERATED LIST */

    std::vector<Company> allCompanies = buildSortedCompanies(lists);

    path = "data/sorted_companies.txt";
    std::ofstream sortedOutput(path);
    if (sortedOutput.fail()) {
        std::cout << "Error creating sorted_output.txt" << std::endl;
        return 0;
    }
    if (sortedOutput.is_open()) {
        for (Company c: allCompanies)
            sortedOutput << c << "\n";
        sortedOutput.close();
    }

    path = "data/past_companies.txt";
    std::ofstream ammendPastData;
    ammendPastData.open(path);
    if (ammendPastData.fail()) {
        std::cout << "Error writing to past_companies.txt" << std::endl;
        return 0;
    }
    if (ammendPastData.is_open()) {
        for (std::string str: pastDataVec)
            ammendPastData << str << "\n";
        ammendPastData.close();
    }

}