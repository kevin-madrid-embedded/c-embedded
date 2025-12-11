#include"getBit.h"
#include"../printb/printb.h"

unsigned char getBit(unsigned char byte, unsigned char bit){
    unsigned char mask = 0x01;
    unsigned char preOut = 0x00;
    if(bit > 7)
        return byte;
    printb(~(mask << bit));
    return byte & mask << bit; 
}

