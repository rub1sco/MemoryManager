#include <iostream>
#include "functions.cpp"



//main driver for application
int main(int argc, const char * argv[]) {
    char userInput;
    bool run = true;

    //declare unordered map for backing store
    unordered_map<int, string> backingStore;
    
    //populate backingStore with data
    buildBackingStore(backingStore);
  
    //TODO figure out why this prints out backwards???? not really important but WHY?!
//    for (auto it = backingStore.begin(); it != backingStore.end(); it++) {
//        printf("frame: %d, appID: %s \n",(*it).first, (*it).second.c_str());
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
                locateRandomAddress(backingStore);
                break;
                
            case 'b':
            case 'B':
                locateKnownAddress(backingStore);
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
