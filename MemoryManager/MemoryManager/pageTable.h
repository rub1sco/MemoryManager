#ifndef pageTable_h
#define pageTable_h
#include <unordered_map>

using namespace std;

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
    int page;       //will we need these?
    int pageSize;   //will we need these?
    int NumPages;   //allows for adjustable table size (if user wants smaller page table)
    unordered_map<int, int> table;
    
public:
    pageTable();
    ~pageTable();
    
    //getters/setters
    int getNumPages();
    void setNumPages(int val);
    void setPageTable(unordered_map<int, int> newTable);
    unordered_map<int, int> getTable();
    
    //methods
    bool bisInTable(int page);
    void addToTable(int page, int frame);
    void removeFromTable(int page);
    
    
};

#endif /* pageTable_h */
