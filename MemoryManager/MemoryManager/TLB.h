#ifndef TLB_h
#define TLB_h

//Contains Translational look aside buffer class

/*
 specs from p-56
 16 entries in TLB
 frame size 2^8 bytes
 256 frames
 phys memory = 65536 bytes (256 frames * 256 byte frame size)
 */


class TLB{
private:
    
    //values on table
    int pageNumber;
    int frameNumber;
    
public:
    
    //getters/setters
    
    //methods needed
    bool bIsInBuffer(int pageNumber, int frameNumber);
    
};


#endif /* TLB_h */
