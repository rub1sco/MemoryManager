#include <iostream>
#include "functions.h"

using std::get;

//main driver for application
int main(int argc, const char * argv[]) {
    
    //initialize variables
    int lookupAddress = 0;
    std::tuple<int,int> physTranslation;
    TLB TLB;
    pageTable pageTable;
    
    
    //generate random address with randomNumberGenerator()
    lookupAddress = randomNumberGenerator();
    
    //parse logical address to page number and page offset
    physTranslation = parser(lookupAddress);
    
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
    
    return 0;
}
