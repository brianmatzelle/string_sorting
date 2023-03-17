#ifndef MISC_H_
#define MISC_H_
#include <string>
#include <set>
#include <vector>
#include <unordered_map>
#include "company.h"

typedef std::set<std::string> str_s;      // each list is stored in a queue
typedef std::vector<str_s> set_vec;           // the lists (queues) are then stored in a vector

std::vector<Company> buildSortedCompanies(const set_vec &lists);
bool strAreLogicallyEq(const std::string& company1, const std::string& company2);
str_s getPastDataSet();
std::vector<std::string> getPastDataVec();
bool alreadyExists(const std::vector<std::string>& pastData, const std::string& company);

/* DEBUG */
void printPastData(str_s pastData);
/* DEBUG */

#endif