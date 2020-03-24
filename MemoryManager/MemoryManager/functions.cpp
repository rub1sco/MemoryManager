#include <stdio.h>
#include <bitset>
#include "TLB.cpp"
#include "functions.h"
#include "pageTable.cpp"
#include <vector>
#include "victimPage.h"
#include <algorithm>


//generates welcome message
void mainMenu(){
    cout << "Welcome to our virtual memory manager. What would you like to do?" << endl;
      cout << "A. Locate random logical addresses" << endl;
      cout << "B. Enter known logical address (0-65535)" << endl;
      cout << "X. exit" << endl;
}

//provides random logical address for lookup
int randomNumberGenerator(){
    int randVal = 0;
    
    //generates random seed
    srand((unsigned)time(NULL));
    
    //logical addresses can be up to 2^16 = 65536
    randVal = rand() % MAX_LOGICAL_ADDR + 1;
    
    return randVal;
}

//parses the logical address into pageNumber and offset
std::tuple<int,int> parser(int logicalAddress, int NumPages){
    int pageNumber = 0;
    int offset = 0;
    
    //error handling if out of bounds value entered
    if(logicalAddress < 0 || logicalAddress > MAX_LOGICAL_ADDR){
        cout << "not a valid value. Please enter within logical addressrange (0,65535)" << endl << endl;
        return std::make_tuple<int,int>(-1,-1);
    }
    
    //converts logical address to 16bit binary string
    string binary = std::bitset<16>(logicalAddress).to_string();
    
    //split into two 8 binary strings
    string strPgNum = binary.substr(8,16);
    string strOffset = binary.substr(0,8);
    
    //convert binary to int
    pageNumber = stoi(strPgNum,nullptr,2);
    offset = stoi(strOffset,nullptr,2);
    
    return std::make_tuple(pageNumber,offset);
}


TLB replacePage (vector<victimPage> & TLBVec, int pageNumber, pageTable pageTable,  TLB TLB)
{
    bool notInPagetable = false;
    int replacementPg = -1;
    int replacementFr = -1;
    unordered_map<int, int> TLB_ = TLB.getLookBuffer();
    unordered_map<int, int> pageTable_ = pageTable.getTable();
    int frame = -1;
    
    // page fault case one: TLB is not full
    // assuming TLB size is 10
    // just look for pg in pg table or in disk and update TLB
    // missing parts - searching disk and updating page table
    
    if (TLB_.size() < 16)
    {
        // look for page number in pageTable
        for (auto i : pageTable_)
        {
            if (i.first == pageNumber)
            {
                TLB.addValue(pageNumber, i.second);
                return TLB;
            }
            else
                notInPagetable = true;
        }
        if (notInPagetable == true)
        {
            frame = randomNumberGenerator();
            pageTable.addToTable(pageNumber, frame);
            TLB.addValue(pageNumber, frame);
        }
    }
    
    // page fault case two: TLB is full, pick a victim page
    if (TLB_.size() == 16)
    {
        cout << "TLBVec before sorting" << endl;
        for (int i = 0; i <TLBVec.size(); i++)
        {
            cout << TLBVec[i].getTally();
        }
        cout  << endl;
        // sort vec on tally thus slot [0] will contain victim pg
        sort(TLBVec.begin(), TLBVec.end());
        cout << "TLBVec after sorting" << endl;
        //        for (int i = 0; i <TLBVec.size(); i++)
        //        {
        //            cout << TLBVec[i].getTally();
        //        }
        //        cout  << endl;
        
        //find pg requested in pg table / disk
        for (auto i : pageTable_)
        {
            if (i.first == pageNumber)
            {
                replacementPg = i.first;
                replacementFr = i.second;
            }
            else
                notInPagetable = true;
        }
        if (notInPagetable == true)
        {
            frame = randomNumberGenerator();
            // page table now has the needed page so now in a recursion call will find the pg in the page table and pick a victim page from the TLB
            pageTable.addToTable(pageNumber, frame);
            replacePage (TLBVec, pageNumber, pageTable, TLB);
            
        }
        
        // find victim in TLB and replace it with the requested retrieved pg
        for (auto i : TLB_)
        {
            if (i.first == TLBVec[0].getPageNum())
            {
                // assuming value also gets erased
                TLB.removeValue(TLBVec[0].getPageNum());
                TLB.addValue(replacementPg, replacementFr);
            }
        }
        
    }
    
    return TLB;
}

// if a TLB hit, update tally
vector<victimPage> updateTally(TLB TLB, int cpu_pg, vector<victimPage> & TLBVec, bool firstOccurrence)
{
    
    victimPage entry;
    vector<victimPage> temp;
    temp = TLBVec;
    TLBVec.clear();
    unordered_map<int, int> TLB_ = TLB.getLookBuffer();
    
    // populates vector with contents of TLB
    if (TLB_.empty() == false)
    {
        for (auto i : TLB_)
        {
            entry.setTally(1);
            entry.setPageNum(i.first);
            entry.setFrameNum(i.second);
            TLBVec.push_back(entry);
        }
    }
    
    // updates tally and keeps size and contents of TLB and vector matching
    for (int i =0; i < temp.size(); i++)
    {
        for (int j = 0; j < TLBVec.size(); j++)
        {
            if (temp[i].getPageNum() == TLBVec[j].getPageNum())
            {
                TLBVec[j].setTally(temp[i].getTally());
            }
        }
    }
    
    // increases tally of requested page if that page was already in TLB
    if (TLBVec.empty() == false && firstOccurrence == false)
    {
        for (int i = 0; i < TLBVec.size(); i++)
        {
            if (cpu_pg == TLBVec[i].getPageNum())
            {
                TLBVec[i].setTally(TLBVec[i].getTally()+1);
            }
        }
    }
    
    return TLBVec;
}


//decides if it is matched in TLB, page table or if page faulted.
//TODO make functional... bulk of alg should be here
void decisionMaker(int pageNumber, int offset, TLB TLB, pageTable pageTable, vector<victimPage> & TLBVec){
    //try and match in TLB
    if(TLB.bIsInBuffer(pageNumber) == true){
        /* do stuff with data here*/
        
        //returns frame number
        
        //use frame and offset to find in physical memory
        int firstOccurrence = false;
        updateTally(TLB, pageNumber, TLBVec, firstOccurrence);
        
    }
    if(TLB.bIsInBuffer(pageNumber) == false)
    {
        
        int firstOccurrence = true;
        TLBVec = updateTally(TLB, pageNumber, TLBVec, firstOccurrence);
        TLB = replacePage(TLBVec, pageNumber, pageTable, TLB);
        TLBVec = updateTally(TLB, pageNumber, TLBVec, firstOccurrence);
        
        
    }
    //if not in TLB, check page table
    // size of physical memory is the same as the size of the virtual address space so no need to replace pg in pg table
    else if (pageTable.bisInTable(pageNumber)== true){
        /* do stuff with data here*/
        
        //returns frame number
        
        //use frame and offset to find in physical memory
    }
    //else, page fault
    else if (pageTable.bisInTable(pageNumber)== false)
    {
        int firstOccurrence = true;
        TLBVec = updateTally(TLB, pageNumber, TLBVec, firstOccurrence);
        TLB = replacePage(TLBVec, pageNumber, pageTable, TLB);
        TLBVec = updateTally(TLB, pageNumber, TLBVec, firstOccurrence);
    }
    
}

//function that locates a random address and determines if in TLB, page number, offset
void locateRandomAddress(){
    int logicalAddress = 0;
    std::tuple<int,int> physTranslation;
    TLB TLB;
    pageTable pageTable;
    vector<victimPage> TLBVec;
    
    //generate random address with randomNumberGenerator()
    logicalAddress = randomNumberGenerator();
    
    cout << "Logical address: " << logicalAddress << endl;
    
    //parse logical address to page number and page offset, returned as tuple in that format
    physTranslation = parser(logicalAddress, pageTable.getNumPages());
    
    //invalid value
    if (get<0>(physTranslation) == -1 && get<1>(physTranslation) == -1){
        return;
    }
    
    //console output for testing
    cout << "Page number: " << get<0>(physTranslation) << endl;
    cout << "Offset: " << get<1>(physTranslation) << endl << endl;
    
    //determines if in TLB, page table or if page fault.. bulk of alg should be here
    decisionMaker(get<0>(physTranslation), get<1>(physTranslation), TLB, pageTable, TLBVec);
}


//looks up known user input
//Note: I thought of this just to add a little more functionality to our virtual memory manager. should be straightforward application of random
void locateKnownAddress(){
    //initialize variables
    int logicalAddress = 0;
    std::tuple<int,int> physTranslation;
    TLB TLB;
    pageTable pageTable;
    vector<victimPage> TLBVec;
    
    cout << "Please enter a logical address: ";
    cin >> logicalAddress;
    
    if(logicalAddress > MAX_LOGICAL_ADDR || logicalAddress < 0){
        cout << "invalid number. Out of bounds." << endl << endl;
        //flushes cin buffer if number is too large
        cin.clear();
        return;
    }
        
    //parse logical address to page number and page offset, returned as tuple in that format
    physTranslation = parser(logicalAddress, pageTable.getNumPages());
    
    //error handling for invalid value
    if (get<0>(physTranslation) == -1 && get<1>(physTranslation) == -1){
        return;
    }
    
    cout << "Page number: " << get<0>(physTranslation) << endl;
    cout << "Offset: " << get<1>(physTranslation) << endl << endl;
    
    //determines if in TLB, page table or if page fault... bulk of alg should be here
    decisionMaker(get<0>(physTranslation), get<1>(physTranslation), TLB, pageTable, TLBVec);
    
}


