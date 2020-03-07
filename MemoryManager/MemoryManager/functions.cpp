#include <stdio.h>
#include "functions.h"

#define MAX_LOGICAL_ADDR 65536

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
    if(logicalAddress < 0 || logicalAddress > 65535){
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


//function to replace page when page fault occurs
//TODO make functional
void replacePage(int pageNumber, int offset){
    /* do stuff with data here*/
}

//decides if it is matched in TLB, page table or if page faulted.
//TODO make functional... bulk of alg should be here
void decisionMaker(int pageNumber, int offset, TLB TLB, pageTable pageTable){
    //try and match in TLB
    if(TLB.bIsInBuffer(pageNumber, offset) == true){
        /* do stuff with data here*/
    }
    //if not in TLB, check page table
    else if (pageTable.bisInTable(pageNumber)== true){
       /* do stuff with data here*/
    }
    //else, page fault
    else{
        replacePage(pageNumber, offset);
    }
    
}

//function that locates a random address and determines if in TLB, page number, offset
void locateRandomAddress(){
    int logicalAddress = 0;
    std::tuple<int,int> physTranslation;
    TLB TLB;
    pageTable pageTable;
    
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
    decisionMaker(get<0>(physTranslation), get<1>(physTranslation), TLB, pageTable);
}


//looks up known user input
//Note: I thought of this just to add a little more functionality to our virtual memory manager. should be straightforward application of random
void locateKnownAddress(){
    //initialize variables
    int logicalAddress = 0;
    std::tuple<int,int> physTranslation;
    TLB TLB;
    pageTable pageTable;
    
    cout << "Please enter a logical address: ";
    cin >> logicalAddress;
    
    if(logicalAddress > 65535 || logicalAddress < 0){
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
    decisionMaker(get<0>(physTranslation), get<1>(physTranslation), TLB, pageTable);
    
}


