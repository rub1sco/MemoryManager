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
tuple<int,int> parser(int logicalAddress);
void updateTally(int cpu_pg, vector<victimPage> & TLBVec, bool firstOccurrence, int & LRU_Tracker);
void replacePage (vector<victimPage> & TLBVec, int pageNumber, int addressToLocate, pageTable & pageTable,  TLB &TLB, int & LRU_Tracker);
void mainMenu();
void locateRandomAddress(vector<victimPage> & TLBVec, pageTable & pageTable, TLB & TLB);
void locateKnownAddress(vector<victimPage> & TLBVec, pageTable & pageTable, TLB & TLB, int & LRU_Tracker);
void demoExample();
void decisionMaker(unordered_map<int, int> &physTranslation, TLB &TLB, pageTable &pageTable, vector<victimPage> & TLBVec);
void decisionMaker(tuple<int,int> physTranslation, TLB &TLB, pageTable &pageTable, vector<victimPage> & TLBVec, int & LRU_Tracker);
void buildBackingStore(Application backingStore[]);
Application fetchFromBkStr(int frame, int offset);

#endif /* functions_h */
