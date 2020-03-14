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

 When a value is inserted into the page table it should be page number is the key,
 frame number is the value.

 */

/* Note: I have only made what I needed to make the stubs work... p
robably needs a lot of modifications and cleaning up*/

class TLB{
private:

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
    void addValue (int pageNumber, int frameNumber);

    //Removes a value from the map by key.
    void removeValue(int valToRemove);

};


#endif /* TLB_h */
