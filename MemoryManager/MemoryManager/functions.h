#ifndef functions_h
#define functions_h
#include <tuple>
#include "pageTable.h"
#include "TLB.h"

//definitons of helper functions

int randomNumberGenerator();
std::tuple<int,int> parser(int logicalAddress);
void replacePage(std::tuple<int,int> parsedData);

#endif /* functions_h */
