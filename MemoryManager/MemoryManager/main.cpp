#include <iostream>
#include "functions.cpp"


//main driver for application
int main(int argc, const char * argv[]) {
    char userInput;
    bool run = true;

    //************************************TEST CODE********************************************//

    //TLB class declaration
    TLB myTLB;

    //Add value to the buffer in the TLB
    myTLB.addValue(18);

    //Check to see if the value was added
    bool check = myTLB.bIsInBuffer(18);

    //Check to ensure we do not get false positives
    check = myTLB.bIsInBuffer(19);

    //Insert new map into TLB
    unordered_map<int, int> newMap;

    //Check the getter
    newMap = myTLB.getLookBuffer();

    //Add a value to the buffer copy
    newMap.insert({20,20});

    //Put the copy of the buffer back into myTLB to check setter
    myTLB.setUnorderedMap(newMap);

    //Check that correct map is in myTLB
    check = myTLB.bIsInBuffer(20);

    //***********************************END TEST CODE********************************************//
    
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
                locateRandomAddress();
                break;
                
            case 'b':
            case 'B':
                locateKnownAddress();
                break;
                
            /* should we add any other options like modifying page sizes or anything???*/
                
            
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
