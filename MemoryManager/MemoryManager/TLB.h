#ifndef TLB_h
#define TLB_h
#include <unordered_map>
using namespace std;

//Contains Translational look aside buffer class

/*
 specs from p-56
 16 entries in TLB
 frame size 2^8 bytes
 256 frames
 phys memory = 65536 bytes (256 frames * 256 byte frame size)
 */

/* Note: I have only made what I needed to make the stubs work... p
robably needs a lot of modifications and cleaning up*/

class TLB{
private:

    //We assume our page size is 256 bytes
    //We assume 256 entries in our page table
    //We assume The size of our logical address space to be 512 addresses
    //We assume there are 128 entries in our translational lookaside buffer
    //We assume the size of the physical memory space to be 1024



    //The actual buffer that will store some of the page numbers from our page table
    unordered_map <int, int> lookBuffer;
    //values on table
    int pageNumber;
    int frameNumber;
    int table [16];
    
    
public:

    //Default constructor sets the size of the lookBuffer
    TLB();

    //Parameterized constructor allows the entry of values into look buffer
    TLB(int entryArray []);

    //Default destructor
    ~TLB();
    
    //*****************Getters and setters**************//

    //Returns the lookBuffer
    unordered_map<int, int> getLookBuffer();

    //Allows entry of a new lookBuffer
    void setUnorderedMap(unordered_map<int, int> newMap);

    //****************End Getters and setters**********//

    //Returns a true if the value is in the buffer
    bool bIsInBuffer(int pageNumber);

    //Places an identical key, value pair in the buffer
    void addValue (int newValue);

};


#endif /* TLB_h */
