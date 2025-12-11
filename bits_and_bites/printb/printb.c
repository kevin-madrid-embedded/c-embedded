#include"printb.h"


void printb(unsigned char byte){
    unsigned char index = 0;
    unsigned char byteOut[9]="00000000";
    //byteOut[8] = '\0'; 
    while(byte){
        if((BITMASK & byte) != 0){
            byteOut[index] = '1';
	}
        else{
            byteOut[index] = '0';
        }
        index++;
        byte = byte << 1;
    }
    printf("\n0b%s\n",byteOut);
}

/*
int main(){
    unsigned char test = 0x55;
    printf("0x%x",test);
    printb(test);
    return 0;
}
*/
