#include <stdio.h>
#include <string.h>
#include <stdlib.h>

    
typedef signed char byte;
    
FILE *addresses, *correct, *backingStore;
char buf[16];
long int addressArray[1000]; //creates an array which we will store out data in
long int pageNumber[1000]; //creates an array that stores the pageNumbers
long int offset[1000]; //creates an array that stores the offsets
long int longInt;

char *pageFrame;// = malloc(256 * sizeof(char)) ; //allocates 256 bytes of space for the the page frame from memory
char *tempChar;
int count, seekTo, physMemCount = 0, tlbCount = 0, numPageFaults = 0, tlbHitRate = 0;
    
byte physicalMem[65536]; //memory of 2^8 * 2^8 bytes 
byte tlb[2][16]; //translation lookaside buffer
byte pageTable[256];

void printAddress(long int virtualAddress, long int physicalAddress, int value) {
    
    printf("Virtual Address: %-6ld Physical Address: %-6ld Value: %-6d\n", virtualAddress, physicalAddress, value);
}


int checkTLB(int num, int offset) { //checks if a given frame is in the TLB
    int pageNum = pageNumber[num], j, value;
    //printf("searching for pageNum: %d in TLB", num);
    
    for (j = 0; j < 16; j++) {
        if (tlb[0][j] == pageNum) {
            printf("TLB hit\n");
            tlbHitRate++;
            value = physicalMem[pageTable[pageNum] * 256 + offset]; //gets value by multiplying reference in pageTable by 256 bytes, and adding the offset
            printAddress(addressArray[num], pageTable[pageNum] * 256 + offset, value);
            return -1;
        }
    }
    //must add the the given page to the TLB
    tlbCount = (tlbCount + 1) % 16;
    
    //printf("TLB miss...Adding page %d to TLB[%d]\n", num, tlbCount);
    tlb[0][tlbCount] = pageNum; //adds page to the TLB. Modulo makes i wrap around to the beginning of the array

    return j; //TLB miss, returns the location to update the TLB at. TLB must be updated later
    
}

int checkPageTable(int num, int offset, int TLBlocation) { //check if a given page is in the pageTable
    int pageNum = pageNumber[num], value, i, temp;

    if (pageTable[pageNum] == 0) { //fetches page from memory, stores it in physicalMemory
        //printf("page fault...adding page %d to pageTable at location %d in physmemory\n", pageNum, physMemCount);
        
        numPageFaults++;
        pageTable[pageNum] = physMemCount; //pageTable points to the first point in memory that stores the respective page
        tlb[1][TLBlocation] = physMemCount;
        
        //must seek to correct frame in BinaryStore to get the page
        pageFrame = malloc(256 * sizeof(char));
        seekTo = pageNum * 256; //seeks to pageNum * 256 bytes
        fseek(backingStore, seekTo, SEEK_SET);
        fread(pageFrame, 256, 1, backingStore);

        //makes the frame in physicalMem equal to the pageFrame returned from backingStore
        temp = physMemCount * 256;
        for (i = 0; i < 256; i++) {
            
            physicalMem[temp + i] = pageFrame[i];
        }
        physMemCount++;
        value = pageFrame[offset];
        //printf("logical address: %-6ld pageNumber: %-6ld offset: %-6d value:%-6d \n", addressArray[num], pageNumber[num], offset,  value);
        printAddress(addressArray[num], temp + offset, value);


    }
    else {
        //printf("   pageNum: %d pageTable[%d]: \n", pageNum, (unsigned int)pageTable[pageNum]);
        //printf("pageTable hit, going to location %ld in memory\n", (long int) pageTable[pageNum] * 256 + offset);
        
        value = physicalMem[pageTable[pageNum] * 256 + offset]; //gets value by multiplying reference in pageTable by 256 bytes, and adding the offset
        //printf("logical address: %-6ld pageNumber: %-6ld offset: %-6d value:%-6d \n", addressArray[num], pageNumber[num], offset,  value);
        printAddress(addressArray[num], pageTable[pageNum] * 256 + offset, value);
    }
    
    
}

int main() {
    int i = 0, temp, loopCount;
    addresses = fopen("addresses.txt","r");
    backingStore = fopen("BACKING_STORE.bin", "rb");
    
    if (!addresses || !backingStore) {
        printf("File does not exist");
        return 1; 
    }
    
    count = 0;
    while (fgets(buf,16, addresses)!=NULL)  {//will run 1000 times, parsing the input files
        longInt = strtol(buf, NULL, 10);
        addressArray[count] = longInt;
        pageNumber[count] = (longInt >> 8) & 0xff;
        offset[count] = longInt & 0xff;
        count++;
    }
    
    for (i = 0; i < 16; i++) {
        tlb[0][i] = -1; //initializes all page values in TLB to -1, indicating they are empty
        tlb[1][i] = 0; //initializes frame values in TLB to 0, indicating they are empty
    }
    for (i = 0; i < 256; i++) {
        pageTable[i] = 0; //intializes all bytes in pageTable to 0
    }
    
    
    loopCount = 200;
    
   for (i = 0; i < loopCount; i++) {

      //  pullFromBackingStore(i, offset[i]);
       temp = checkTLB(i, offset[i]);
       if (temp != -1) { //if checkTLB returns a TLB miss, then we check in the page table
            checkPageTable(i, offset[i], temp);
       }
    }
    printf("Page fault rate: %f TLB hit rate: %f\n", (double)numPageFaults / loopCount * 100, (double) tlbHitRate / loopCount * 100);
    
}