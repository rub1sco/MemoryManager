#include <stdio.h>
#include "TLB.h"

TLB::TLB(){

    //Reserve the required number of spaces for our TLB.
    lookBuffer.reserve(128);

    //Possibly load entries into the buffer

}//end default constructor

TLB::TLB(int entryArray []){

    //Implement functionality.....

}//end parameterized constructor



TLB::~TLB(){
    
}

unordered_map <int, int> TLB:: getLookBuffer(){

    return lookBuffer;

}//end getLookBuffer

void TLB:: setUnorderedMap(unordered_map <int, int> newMap){

    lookBuffer = newMap;

}//end setUnorderedMap

bool TLB::bIsInBuffer(int pageNumber){

    //Declare an iterator for an unordered_map
    unordered_map<int, int>::iterator mapIt;

    //Look for page number in buffer
    mapIt = lookBuffer.find(pageNumber);

    //Check if iterator returned end.
    //If the iterator returned end the item was not in the buffer.
    if(mapIt == lookBuffer.end()){

        return false;
    }//end if

    //If the iterator is not at the end, the buffer has returned a number.
    else if(mapIt != lookBuffer.end()){

        return true;

    }//end else if

}//end bool TLB::bIsInBuffer()

void TLB::addValue(int newValue){

    lookBuffer.insert({newValue, newValue});

}//end addValueToMap