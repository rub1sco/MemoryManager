#ifndef functions_h
#define functions_h
#include <tuple>
#include "pageTable.h"
#include "TLB.h"
#include <time.h>
#include <iostream>
#include <string>
#include <sstream>


#define MAX_LOGICAL_ADDR 65535

using namespace std;

//definitons of helper functions
int randomNumberGenerator();
tuple<int,int> parser(int logicalAddress, int NumPages);
void replacePage(int pageNumber, int offset);
void mainMenu();
void locateRandomAddress();
void locateKnownAddress();
void decisionMaker(int pageNumber, int offset, TLB TLB, pageTable pageTable);

#endif /* functions_h */
