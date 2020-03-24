#ifndef functions_h
#define functions_h
#include <tuple>
#include "pageTable.h"
#include "TLB.h"
#include <time.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "victimPage.h"
#include <algorithm>


#define MAX_LOGICAL_ADDR 65535

using namespace std;

//definitons of helper functions
int randomNumberGenerator();
tuple<int,int> parser(int logicalAddress, int NumPages);
vector<victimPage> updateTally(unordered_map<int, int> TLB, int cpu_pg, vector<victimPage> & TLBVec, bool firstOccurrence);
TLB replacePage (vector<victimPage> & TLBVec, int pageNumber, pageTable pageTable,  TLB TLB);
void mainMenu();
void locateRandomAddress();
void locateKnownAddress();
void decisionMaker(int pageNumber, int offset, TLB TLB, pageTable pageTable, vector<victimPage> & TLBVec);

#endif /* functions_h */
