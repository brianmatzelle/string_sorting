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
bool strAreLogicallyEq(const std::string& company1, const std::string& company2);
str_q getPastDataQ();
std::vector<std::string> getPastDataVec();
bool alreadyExists(const std::vector<std::string>& pastData, const std::string& company);

/* DEBUG */
void printPastData(str_q pastData);
/* DEBUG */

#endif