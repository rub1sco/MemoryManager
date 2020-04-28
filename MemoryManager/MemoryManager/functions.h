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

struct Application {
    int frame;
    string appName;
};


//definitons of helper functions
int randomNumberGenerator();
tuple<int,int> parser(int logicalAddress, int NumPages);
vector<victimPage> updateTally(unordered_map<int, int> TLB, int cpu_pg, vector<victimPage> & TLBVec, bool firstOccurrence);
TLB replacePage (vector<victimPage> & TLBVec, int pageNumber, pageTable pageTable,  TLB TLB, Application backingStore[]);
void replacePageV2(vector<victimPage> & TLBVec, int pageNumber, pageTable pageTable,  TLB TLB, Application backingStore[]);
void mainMenu();
void locateRandomAddress(Application backingStore[]);
void locateKnownAddress(Application backingStore[]);
void decisionMaker(tuple<int,int> physTranslation, TLB TLB, pageTable pageTable, vector<victimPage> & TLBVec, Application backingStore[]);
void buildBackingStore(Application backingStore[]);

#endif /* functions_h */
