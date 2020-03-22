#include <stdio.h>
#include "TLB.h"

TLB::TLB(){

    //Reserve the required number of spaces for our TLB.
    lookBuffer.reserve(16);
    
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


    //If the iterator is not at the end, the buffer has returned a number.
    if(mapIt != lookBuffer.end()){

        return true;

    }//end else if

    //did not find in TLB
    return false;

}//end bool TLB::bIsInBuffer()

void TLB::addValue(int pageValue, int frameNumber){

    lookBuffer.insert({pageValue, frameNumber});

}//end addValueToMap

void TLB::removeValue(int valToRemove) {

    lookBuffer.erase(valToRemove);

}//end removeValue
