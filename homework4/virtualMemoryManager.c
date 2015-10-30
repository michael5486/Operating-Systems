#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    
    FILE *addresses, *correct, *backingStore;
    char buf[16];
    long int addressArray[1000]; //creates an array which we will store out data in
    long int pageNumber[1000];
    long int offset[1000];
    long int longInt;
    unsigned char physicalMem[65536]; //memory of 2^8 * 2^8 bytes 
    unsigned char tlb[2][16]; //translation lookaside buffer
    unsigned char pageTable;
    char *pageFrame;// = malloc(256 * sizeof(char)) ; //allocates 256 bytes of space for the the page frame from memory
    char* tempChar;
    int count, i, seekTo;
    
    
    
    addresses = fopen("addresses.txt","r");
    correct = fopen("correct.txt", "r");
    backingStore = fopen("BACKING_STORE.bin", "rb");
    
    
    
    if (!addresses || !correct || !backingStore) {
        printf("File does not exist");
        return 1; 
    }
    
    count = 0;
    while (fgets(buf,16, addresses)!=NULL)  {//will run 1000 times
        longInt = strtol(buf, NULL, 10);
        addressArray[count] = longInt;
        pageNumber[count] = (longInt >> 8) & 0xff;
        offset[count] = longInt & 0xff;
        count++;
        
    }
    pageFrame = malloc(256 * sizeof(char));
    for (i = 0; i < 1000; i++) {
        seekTo = pageNumber[i] * 256;
        fseek(backingStore, seekTo, SEEK_SET);
        fread(pageFrame, 256, 1, backingStore);
        printf("logical address: %-6ld pageNumber: %-6ld offset: %-6ld seekTo: %-6d value:%-6d \n", addressArray[i], pageNumber[i], offset[i], seekTo, pageFrame[offset[i]]); //last number messes up for some reason
    }
    
    //want to get to page number 12032. must navigate to 12032 * 256th byte in BACKING_STORE and the offset 75 bytes
    
    //size_t fread ( void * ptr, size_t size, size_t count, FILE * stream );
    //int fseek ( FILE * stream, long int offset, int origin );
    //fseek(backingStore, 256 * 244 + 75, SEEK_END);
    //fileLen = ftell(backingStore);
   // fseek(backingStore, 47 * 256, SEEK_SET);
    //fread(pageFrame, 256, 1, backingStore);
    //for (i = 0; i < 256; i++) {   
      //  printf("Pageframe[%d] = %d\n", i, pageFrame[i]);
    //}
    //printf("length: %d", fileLen);
    
    
    
        
}