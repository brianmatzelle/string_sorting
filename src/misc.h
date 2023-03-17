#ifndef MISC_H_
#define MISC_H_
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include "company.h"

typedef std::queue<std::string> str_q;      // each list is stored in a queue
typedef std::vector<str_q> q_vec;           // the lists (queues) are then stored in a vector

std::vector<Company> buildSortedCompanies(q_vec &lists);
bool strAreLogicallyEq(std::string company1, std::string company2);
std::unordered_map<std::string, unsigned> getPastData();
bool alreadyExists(std::unordered_map<std::string, unsigned> &pastData, std::string company);

/* DEBUG */
void printPastData(std::vector<std::string> pastData);
/* DEBUG */

#endif