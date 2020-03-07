#include <iostream>
#include "functions.h"


//main driver for application
int main(int argc, const char * argv[]) {
    char userInput;
    bool run = true;
    
    while (run) {
        //welcome message with main menu prompt
        mainMenu();
        
        //gets user input
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
