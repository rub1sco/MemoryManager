#ifndef pageTable_h
#define pageTable_h



/*
 specs from p-56
 2^8 entries in page table
 page size = 2^8 bytes
 physical memory is 65,536 bytes
 */

/* Note: I have only made what I needed to make the stubs work... p
 robably needs a lot of modifications and cleaning up*/

class pageTable{
private:
    int page;
    int pageSize;
    int NumPages;
    
public:
    pageTable();
    ~pageTable();
    
    //getters/setters
    int getNumPages();
    
    
    //methods
    bool bisInTable(int page);
    
};

#endif /* pageTable_h */
