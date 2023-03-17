#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include "jaro.h"
#include "company.h"
#include "misc.h"

int main(int argc, char *argv[]) {
    // THIS PROGRAM MUST BE RUN FROM THE ROOT DIRECTORY, OTHERWISE FILE STREAMS WON'T OPEN CORRECTLY


    /* INITIATE LISTS */
    q_vec lists;    // q_vec defined in misc.h (vec of lists)
    if (argc > 1) {
        std::cout << "ERROR: no arguments needed for this program." << std::endl;
        return 0;
    }
    int list_count = 2;     // is this always true? same line in python file
    for (int i = 0; i < list_count; i++) {
        lists.push_back(str_q());           // each list is a queue, the queues are then stored in this var
    }
    /* INITIATE LISTS */


    /* GET PAST DATA (pseudo database) */
    std::vector<std::string> pastData = getPastData();
    /* GET PAST DATA (pseudo database) */


    /* PARSE THROUGH PYTHON GENERATED LIST */
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
        std::string line;
        getline(parsedFile, line);
        if (line == "") {                // this counter only works because of the formatting of sheet_contents.txt (it starts with \n and has a \n after every list)
            list_i++;
            continue;
        }
        // lists[list_i].push(line);     // add the company string to its list's queue
        else if ( !alreadyExists(pastData, line) )
            lists[list_i].push(line);
        else
            continue;
    }
    /* PARSE THROUGH PYTHON GENERATED LIST */

    std::vector<Company> allCompanies = buildSortedCompanies(lists);

    sortedOutput.open("interim/sorted_companies.txt", std::ios_base::app);
    if (sortedOutput.is_open()) {
        for (Company c: allCompanies)
            sortedOutput << c << "\n";
        sortedOutput.close();
    }
}