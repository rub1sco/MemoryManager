#include <stdio.h>
#include "pageTable.h"
#include <iostream>
using namespace std;


//constructor... sets variables and initialzies table
//TODO is page,pageSize necessary?
pageTable::pageTable(){
    //2^8 entries in page table
    //page size = 2^8 bytes
    page = 0;
    pageSize = 256;
    NumPages = 256;
    table.reserve(NumPages);
}

//destructor
pageTable::~pageTable(){
    
}


//copies table with given unordered map.
void pageTable::setPageTable(unordered_map<int, int>newTable){
    table = newTable;
}

//sets number of pages
void pageTable::setNumPages(int val){
    NumPages = val;
}


//returns number of pages in page table
int pageTable::getNumPages(){
    return NumPages;
}

unordered_map <int, int> pageTable:: getTable(){
    
    return table;
    
}

//checks if page is in table
bool pageTable::bisInTable(int page){
    unordered_map<int, int>::iterator tableIter;
    
    tableIter = table.find(page);
    
    if(tableIter != table.end()){
        return true;
    }
    
    return false;
}


//adds to table, checks if value is already present.. cannot load same frame twice (or can you?)
void pageTable::addToTable(int page, int frame){
    
    if(table.count(page) == 1){
        cout << "cannot load duplicate page" << endl;
    }
    else{
        table.insert({page, frame});
    }
}

//removes page from table
void pageTable::removeFromTable(int page){
    table.erase(page);
}

void pageTable::printData(int pageNumber){
    //print data associated with key
    
}
