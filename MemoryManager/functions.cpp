#include "functions.h"
#include <algorithm>
#include "victimPage.h"



//generates welcome message
void mainMenu(){
      cout << "Welcome to our virtual memory manager. What would you like to do?" << endl;
      cout << "A. Locate random logical addresses" << endl;
      cout << "B. Enter known logical address (0-65535)" << endl;
      cout << "C. Project Demo" << endl;
      cout << "X. exit" << endl;
}

void demoExample(){
    
    //generate random logical address
    int logicalAddr = randomNumberGenerator();
    printf("generating address...\n");
    printf("Logical address generated: %d\n", logicalAddr);
    
    //parse into pagenumber and offset
    tuple<int,int> physTranslation = parser(logicalAddr);
    printf("parsing data...\nparsed.\npage number: %d, offset: %d\n fetching from backing store... please wait...\n",get<0>(physTranslation), get<1>(physTranslation));
    
    //fetch from backing store
    fetchFromBkStr(get<0>(physTranslation), get<1>(physTranslation));
}


//provides random logical address for lookup
int randomNumberGenerator(){
    int randVal = 0;

    
    //logical addresses can be up to 2^16 = 65536
    randVal = rand() % MAX_LOGICAL_ADDR + 1;
    
    return randVal;
}

//parses the logical address into pageNumber and offset
std::tuple<int,int> parser(int logicalAddress){
    int pageNumber = 0;
    int offset = 0;
    
    //error handling if out of bounds value entered
    if(logicalAddress < 0 || logicalAddress > MAX_LOGICAL_ADDR){
        cout << "not a valid value. Please enter within logical addressrange (0,65535)" << endl << endl;
        return std::make_tuple<int,int>(-1,-1);
    }
    
    //converts logical address to 16bit binary string
    string binary = std::bitset<16>(logicalAddress).to_string();

    
    //split into two 8 binary strings
    string strPgNum = binary.substr(0,8);
    string strOffset = binary.substr(8,16);

    //convert binary to int
    pageNumber = stoi(strPgNum,nullptr,2);
    offset = stoi(strOffset,nullptr,2);
    
    return std::make_tuple(pageNumber,offset);
}

// if a TLB hit, update tally
void updateTally(TLB & TLB, int cpu_pg, vector<victimPage> & TLBVec, bool firstOccurrence)
{
    
    if (TLBVec.empty() == false && firstOccurrence == false && TLBVec.size() < 16)
    {
        for (int i = 0; i < TLBVec.size(); i++)
        {
            if (cpu_pg == TLBVec[i].getPageNum())
            {
                TLBVec[i].setTally(TLBVec[i].getTally()+1);
            }
        }
    }
    
}

void replacePage (vector<victimPage> & TLBVec, int pageNumber, int addressToLocate, pageTable & pageTable,  TLB & TLB, int LRU_Tracker)

{
    victimPage entry;
    // flag to check if requested pageNumber is in pageTable
    bool bIsInPageTable = false;
    

    unordered_map<int, int> TLB_ = TLB.getLookBuffer();
    unordered_map<int, int> pageTable_ = pageTable.getTable();
    int invalidBit = 0;
  

    
    // page fault case one: TLB is not full
    // TLB size is 16
    // just look for pg in pg table or in disk and update TLB
    
    if (TLB_.size() < 16 && TLBVec.size() < 16)
    {
        
        // look for page number in pageTable
        unordered_map<int, int>::iterator mapItP;
        unordered_map<int, int> pageTable_ = pageTable.getTable();
        mapItP = pageTable_.begin();
        
        while(mapItP != pageTable_.end())
        {
            
            if (mapItP->first == pageNumber)
            {
              
                TLB.addValue(pageNumber, pageNumber);
                entry.setTally(TLBVec.size()+1);
                entry.setPageNum(pageNumber);
                entry.setFrameNum(pageNumber);
                TLBVec.push_back(entry);
                bIsInPageTable = true;
                
                
            }
            // page was not found in page table
            else{
                bIsInPageTable = false;
            }
        mapItP ++;
    }
        
        // page was not found in page table
        if (bIsInPageTable == false)
        {
            // by adding page to pageTable the valid - invalid but is set to 1
            invalidBit = 1;
            pageTable.addToTable(pageNumber, invalidBit);
            TLB.addValue(pageNumber, pageNumber);
            entry.setTally(TLBVec.size()+1);
            entry.setPageNum(pageNumber);
            entry.setFrameNum(pageNumber);
            TLBVec.push_back(entry);
        }
    }
    
    TLB_ = TLB.getLookBuffer();
    
    // page fault case two: TLB is full, pick a victim page
    
    if (TLB_.size() == 16 && TLBVec.size() == 16)
    {
        
        LRU_Tracker ++;
        
        // sort vec on tally thus slot [0] will contain victim pg
        sort(TLBVec.begin(), TLBVec.end());
        //cout << "page to be removed: " << TLBVec[0].getPageNum() << endl;
        
        unordered_map<int, int>::iterator mapIt;
        unordered_map<int, int> TLB_ = TLB.getLookBuffer();
        mapIt = TLB_.begin();
       
        
        // find victim in TLB
        while(mapIt != TLB_.end())
        {
            if (mapIt->first == TLBVec[0].getPageNum())
            {
                // assuming value also gets erased
                TLB.removeValue(TLBVec[0].getPageNum());
                // erase TLBVec[0] from TLBVec
                TLBVec.erase(TLBVec.begin());
                break;
            }
            mapIt ++;
        }
        
        unordered_map<int, int>::iterator mapItP;
        unordered_map<int, int> pageTable_ = pageTable.getTable();
        mapItP = pageTable_.begin();
        
        auto temp = parser(addressToLocate);
        addressToLocate = get<0>(temp);
        int offset = get<1>(temp);
        //Application test;
        //test = fetchFromBkStr(temp, offset);
        
        
        
        //find pg requested in pg table / disk
        while(mapItP != pageTable_.end())
        {

            if (mapItP->first == addressToLocate)
            {
                //cout << "desired page to be added: " << addressToLocate << endl;
                TLB.addValue(addressToLocate, addressToLocate);
                entry.setTally(LRU_Tracker);
                entry.setPageNum(addressToLocate);
                entry.setFrameNum(addressToLocate);
                TLBVec.push_back(entry);
                bIsInPageTable = true;
                break;
            }
            else{
                bIsInPageTable = false;
            }
            mapItP ++;
        }
        
        // page was not found in page table
        if (bIsInPageTable == false)
        {
            invalidBit = 1;
            pageTable.addToTable(addressToLocate, invalidBit);
            //cout << "desired page to be added: " << addressToLocate << endl;
            TLB.addValue(addressToLocate, addressToLocate);
            entry.setTally(LRU_Tracker);
            entry.setPageNum(addressToLocate);
            entry.setFrameNum(addressToLocate);
            TLBVec.push_back(entry);
            
        }
        
    }
    
}

//decides if it is matched in TLB, page table or if page faulted.
void decisionMaker(unordered_map<int, int> &physTranslation, TLB &TLB, pageTable &pageTable, vector<victimPage> & TLBVec, int addressToLocate){
    
    int LRU_Tracker = 16;
    int pageNumber = 0;
    int offset = 0;
    
    unordered_map<int, int>::const_iterator it;
    for(it = physTranslation.begin(); it != physTranslation.end(); it++) {
         pageNumber = (it ->first);
         offset = (it -> second);
    //}
        
        
       if (TLB.bIsInBuffer(pageNumber) == true){
                /* do stuff with data here*/

                //returns frame number

                //use frame and offset to find in physical memory
                int firstOccurrence = false;
                updateTally(TLB, pageNumber, TLBVec, firstOccurrence);

            }
//        if (TLB.bIsInBuffer(pageNumber) == false)
//            {
//                int startLoc = pageNumber + offset;
//                cout << startLoc << endl;
//                 cout << (unsigned char) startLoc << endl;
//
//                 replacePage (TLBVec, pageNumber, pageTable, TLB);
//
//            }
            //if not in TLB, check page table
            // size of physical memory is the same as the size of the virtual address space so no need to replace pg in pg table
             if (pageTable.bisInTable(pageNumber)== true){
                /* do stuff with data here*/

                //returns frame number

                //use frame and offset to find in physical memory
                replacePage (TLBVec, pageNumber, addressToLocate, pageTable, TLB, LRU_Tracker);
            }
            //else, page fault
            if (pageTable.bisInTable(pageNumber)== false)
            {
                replacePage (TLBVec, pageNumber, addressToLocate, pageTable, TLB, LRU_Tracker );
                
            }
        //cout << "at the end of decision maker " <<TLBVec.size() << endl;
    }
    //cout << "end of decisionMaker loop: " <<endl;
        
}


//overloaded decisionMaker to load single app into memory by logical address
void decisionMaker(tuple<int,int> physTranslation, TLB &TLB, pageTable &pageTable, vector<victimPage> & TLBVec){
    int pageNumber = get<0>(physTranslation);
    int offset = get<1>(physTranslation);
    int LRU_Tracker = 16;
    
   if(TLB.bIsInBuffer(pageNumber) == true){
            /* do stuff with data here*/
            
            //returns frame number
            
            //use frame and offset to find in physical memory
            int firstOccurrence = false;
            updateTally(TLB, pageNumber, TLBVec, firstOccurrence);
            
        }
//    if(TLB.bIsInBuffer(pageNumber) == false)
//        {
//            int startLoc = pageNumber + offset;
//            cout << startLoc << endl;
//             cout << (unsigned char) startLoc << endl;
//
//              replacePage (TLBVec, pageNumber, pageTable, TLB);
//
//
//        }
        //if not in TLB, check page table
        // size of physical memory is the same as the size of the virtual address space so no need to replace pg in pg table
        else if (pageTable.bisInTable(pageNumber)== true){
            /* do stuff with data here*/
            
            //returns frame number
            
            //use frame and offset to find in physical memory
             replacePage (TLBVec, pageNumber, pageNumber, pageTable, TLB, LRU_Tracker);
        }
        //else, page fault
        else if (pageTable.bisInTable(pageNumber)== false)
        {
            replacePage (TLBVec, pageNumber, pageNumber, pageTable, TLB, LRU_Tracker);
            
        }
   // cout << "at the end of decision maker the TLBVec size is: " <<TLBVec.size() << endl;
        
}
    

//function that locates a random address and determines if in TLB, page number, offset
void locateRandomAddress(vector<victimPage> & TLBVec, pageTable & pageTable, TLB & TLB){
//    TLB TLB;
//    pageTable pageTable;
//    vector<victimPage> TLBVec;
    int logAddrAry[256];
    unordered_map<int, int> physTranslation;
    
     int addressToLocate = 0;
    
    //generates random seed
    srand((unsigned int) time(NULL));
    for (int i = 0; i < 256; i++) {
        logAddrAry[i] = randomNumberGenerator();
        addressToLocate = logAddrAry[i];
        //cout << "Chill for a moment" << endl;
    }
    

    //physical translation for each address... ****DOES CONTAIN DUPLICATES****
    for (int i = 0; i < 256; i++) {
        auto temp = parser(logAddrAry[i]);
        physTranslation.insert({get<0>(temp),get<1>(temp)});
    }

    
    //determines if in TLB, page table or if page fault.. bulk of alg should be here
    decisionMaker(physTranslation, TLB, pageTable, TLBVec, addressToLocate);
}


//looks up known user input
//Note: I thought of this just to add a little more functionality to our virtual memory manager. should be straightforward application of random
void locateKnownAddress(vector<victimPage> & TLBVec, pageTable & pageTable, TLB & TLB){
    //initialize variables
    int logicalAddress = 0;
    std::tuple<int,int> physTranslation;
//    TLB TLB;
//    pageTable pageTable;
//    vector<victimPage> TLBVec;
    
    cout << "Please enter a logical address: ";
    cin >> logicalAddress;
    
    if(logicalAddress > MAX_LOGICAL_ADDR || logicalAddress < 0){
        cout << "invalid number. Out of bounds." << endl << endl;
        //flushes cin buffer if number is too large
        cin.clear();
        return;
    }
        
    //parse logical address to page number and page offset, returned as tuple in that format
    physTranslation = parser(logicalAddress);
    
    //error handling for invalid value
    if (get<0>(physTranslation) == -1 && get<1>(physTranslation) == -1){
        return;
    }
    
    cout << "Page number: " << get<0>(physTranslation) << endl;
    cout << "Offset: " << get<1>(physTranslation) << endl << endl;
    
    //determines if in TLB, page table or if page fault... bulk of alg should be here
    decisionMaker(physTranslation, TLB, pageTable, TLBVec);
    
}


//generates backing store with keys 0-255, each with a unique "app name"
void buildBackingStore(Application backingStore[]){
    ifstream file("words.txt");
    string line;
    vector<string> words;
    
    while(getline(file, line)){
        words.push_back(line);
    }

    
    //frames build from 0-255, therefore key must be 0-255 with no duplicate
    for (int i = 0; i < 256; i++) {
        //gets randVal within words.txt
        int randVal = rand() % words.size();
        
        //stores randomword
        string randomWord = words[randVal];
        
        //removes from vector to ensure each app is unique
        words[randVal].erase();
        
        //appends .exe to show app executable
        randomWord.append(".exe");
    
        //create application object
        Application frame = Application();
        
        frame.frame = i;
        frame.appName = randomWord;
        
        //add to vector
        backingStore[i]= frame;
        
    }
    
    //write map to binary file
    ofstream BckStrfile("backingStore.bin",ios::out | ios::binary);
    if(!BckStrfile){
        printf("cannot open file.\n");
        return;
    }
    
    //writes backing store array to binary file
    for(int i = 0; i < 256; i++){
        BckStrfile.write((char *) &backingStore[i], sizeof(Application));
    }
    BckStrfile.close();
    

};


//fetches application name from backing store.
Application fetchFromBkStr(int frame, int offset){
    Application foundApp;
    
    FILE *tempFile;
    tempFile = fopen("backingStore.bin", "r");
    fseek(tempFile, (sizeof(Application)* frame), SEEK_SET);
    Application tempApp;
    fread(&tempApp, sizeof(Application), 1, tempFile);
    //cout << tempApp.frame << tempApp.appName << endl;
    printf("physical frame number: %d, stored application: %s\n\n", tempApp.frame, tempApp.appName.c_str());
    
    foundApp.frame = tempApp.frame;
    foundApp.appName = tempApp.appName;
    
    return foundApp;
};

