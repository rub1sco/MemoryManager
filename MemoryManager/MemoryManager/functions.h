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
#include <random>
#include <fstream>


#define MAX_LOGICAL_ADDR 65535

using namespace std;

//definitons of helper functions
int randomNumberGenerator();
tuple<int,int> parser(int logicalAddress, int NumPages);
vector<victimPage> updateTally(unordered_map<int, int> TLB, int cpu_pg, vector<victimPage> & TLBVec, bool firstOccurrence);
TLB replacePage (vector<victimPage> & TLBVec, int pageNumber, pageTable pageTable,  TLB TLB);
void mainMenu();
void locateRandomAddress(unordered_map<int, string>  &backingStore);
void locateKnownAddress(unordered_map<int, string> &backingStore);
void decisionMaker(int pageNumber, int offset, TLB TLB, pageTable pageTable, vector<victimPage> & TLBVec);
void buildBackingStore(unordered_map<int, string> &backingStore);


#endif /* functions_h */
