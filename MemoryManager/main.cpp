#include "functions.h"



//main driver for application
int main(int argc, const char * argv[]) {
    char userInput;
    bool run = true;
    Application backingStore[256];
    vector<victimPage> TLBVec;
    TLB TLB;
    pageTable pageTable;
    int LRU_Tracker = 0;
    //populate backingStore with data
    buildBackingStore(backingStore);
    
    //test print
    //    ifstream rf("backingStore.bin", ios::out | ios::binary);
    //    for(int i = 0; i < 256; i++){
    //        rf.read((char *) &backingStore[i], sizeof(Application));
    //    }
    //    rf.close();
    //    for(int i = 0; i < 256; i++){
    //
    //        cout << backingStore[i].frame << " " << backingStore[i].appName << endl;
    //    }
    
    
    
    //runs main program
    while (run) {
        //welcome message with main menu prompt
        mainMenu();
        
        //gets user input
        cout << "Please enter a selection: ";
        cin >> userInput;
        
        switch (userInput) {
            case 'a':
            case 'A':
                locateRandomAddress(TLBVec, pageTable, TLB);
                break;
                
            case 'b':
            case 'B':
                locateKnownAddress(TLBVec, pageTable, TLB, LRU_Tracker);
                break;
                
                /* should we add any other options like modifying page sizes or anything???*/
                
            case 'c':
            case 'C':
                demoExample();
                break;
                
            case 'x':
            case 'X':
                run =  false;
                break;
                
            default:
                cout << "Please enter valid response." << endl;
                break;
        }
    }
    
    return 0;
}


