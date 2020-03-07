#ifndef pageTable_h
#define pageTable_h


/*
 specs from p-56
 2^8 entries in page table
 page size = 2^8 bytes
 physical memory is 65,536 bytes
 */

class pageTable{
private:
    int page;
    
public:
    //getters/setters
    
    //methods
    bool bisInTable(int page);
    
};

#endif /* pageTable_h */
