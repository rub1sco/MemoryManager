#ifndef functions_h
#define functions_h
#include <tuple>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>

#include "victimPage.h"
#include "TLB.h"
#include "pageTable.h"


#define MAX_LOGICAL_ADDR 65535
//typedef unsigned char Byte;

using namespace std;

struct Application {
    int frame;
    string appName;
};


//definitons of helper functions
int randomNumberGenerator();
tuple<int,int> parser(int logicalAddress, int NumPages);
vector<victimPage> updateTally(unordered_map<int, int> TLB, int cpu_pg, vector<victimPage> & TLBVec, bool firstOccurrence);
TLB replacePage (vector<victimPage> & TLBVec, int pageNumber, pageTable pageTable,  TLB TLB, Application backingStore[]);
void mainMenu();
void locateRandomAddress(Application backingStore[]);
void locateKnownAddress(Application backingStore[]);
void decisionMaker(tuple<int,int> physTranslation, TLB TLB, pageTable pageTable, vector<victimPage> & TLBVec, Application backingStore[]);
void buildBackingStore(Application backingStore[]);
Application fetchFromBkStr(int frame, int offset);

#endif /* functions_h */
