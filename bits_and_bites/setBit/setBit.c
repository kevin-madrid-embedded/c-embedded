#include"setBit.h"

unsigned char setBit(unsigned char byte, unsigned char bit){
    unsigned char mask = 0x80;
    if (bit > 7)
        return byte;
    return byte | mask >> bit - 1 ;
}
