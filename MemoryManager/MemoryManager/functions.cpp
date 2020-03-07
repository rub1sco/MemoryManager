#include <stdio.h>
#include "functions.h"

#define MAX_LOGICAL_ADDR 65536

//generates welcome message
void mainMenu(){
    cout << "Welcome to our virtual memory manager. What would you like to do?" << endl;
      cout << "A. Locate random logical addresses" << endl;
      cout << "B. Enter known logical address (0-65536)" << endl;
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
//TODO make functional
std::tuple<int,int> parser(int logicalAddress){
    int pageNumber = 0;
    int offset = 0;
    
    return std::make_tuple(pageNumber,offset);
}


//function to replace page when page fault occurs
void replacePage(std::tuple<int,int> parsedData){
    
}

//function that locates a random address and determines if in TLB, page number, offset
//TODO possibly modularize by removing logic if/else into different function... also make functional
void locateRandomAddress(){
    int logicalAddress = 0;
    std::tuple<int,int> physTranslation;
    TLB TLB;
    pageTable pageTable;
    
    //generate random address with randomNumberGenerator()
    logicalAddress = randomNumberGenerator();
    
    cout << "Logical address: " << logicalAddress << endl;
    
    //parse logical address to page number and page offset, returned as tuple in that format
    physTranslation = parser(logicalAddress);
    
    cout << "Page number: " << get<0>(physTranslation) << endl;
    cout << "Offset: " << get<1>(physTranslation) << endl;
    
    //try and match in TLB
    if(TLB.bIsInBuffer(get<0>(physTranslation), get<1>(physTranslation)) == true){
        
    }
    //if not in TLB, check page table
    else if (pageTable.bisInTable(get<0>(physTranslation)== true)){
       
    }
    //else, page fault
    else{
        replacePage(physTranslation);
            
    }
}


//looks up known user input
//TODO I thought of this just to add a little more functionality. 
void locateKnownAddress(){
    
}


