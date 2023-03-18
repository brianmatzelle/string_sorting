#ifndef MISC_H_
#define MISC_H_
#include <string>
#include <set>
#include <vector>
#include <unordered_map>
#include "company.h"

typedef std::vector<std::string> str_v;      // each list is stored in a queue
typedef std::vector<str_v> Lists;           // the lists (queues) are then stored in a vector

std::vector<Company> buildSortedCompanies(const Lists &lists);
bool strAreLogicallyEq(const std::string& company1, const std::string& company2);
str_v getPastDataVec();
bool alreadyExists(const std::vector<std::string>& pastData, const std::string& company);

/* DEBUG */
void printPastData(str_v pastData);
/* DEBUG */

#endif