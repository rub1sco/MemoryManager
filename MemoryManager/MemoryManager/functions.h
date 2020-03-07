#ifndef functions_h
#define functions_h
#include <tuple>
#include "pageTable.h"
#include "TLB.h"
#include <time.h>
#include <iostream>

using namespace std;

//definitons of helper functions

int randomNumberGenerator();
std::tuple<int,int> parser(int logicalAddress);
void replacePage(std::tuple<int,int> parsedData);
void mainMenu();
void locateRandomAddress();
void locateKnownAddress();

#endif /* functions_h */
