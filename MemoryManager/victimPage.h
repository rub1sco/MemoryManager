//
//  victimPage.h
//  replacePage_OS
//
//  Created by Nancy Moreno Huizar on 3/18/20.
//  Copyright © 2020 Nancy Moreno Huizar. All rights reserved.
//

#ifndef victimPage_h
#define victimPage_h
using namespace std;

class victimPage {

private:
    int tally = 0;
    int pageNum = -1;
    int frameNum = -1;
    
public:
    void setTally (int _tally) {tally = _tally;}
    int getTally () {return tally;}
    void setPageNum (int _pageNum) {pageNum = _pageNum;}
    int getPageNum () {return pageNum;}
    void setFrameNum (int _frameNum) {frameNum = _frameNum;}
    int getFrameNum () {return frameNum;}
    bool operator < (const victimPage& vpg ) const
    {
        if (tally < vpg.tally)
        {return true;}
        if (tally == vpg.tally)
        {return true;}

        return false;
    }
    
};

#endif /* victimPage_h */
