#include <stdio.h>
#include "pageTable.h"

pageTable::pageTable(){
    //2^8 entries in page table
    //page size = 2^8 bytes
    page = 0;
    pageSize = 256;
    NumPages = 256;
}
pageTable::~pageTable(){
    
}

bool pageTable::bisInTable(int page){
   
    return false;
}

int pageTable::getNumPages(){
    return NumPages;
}
