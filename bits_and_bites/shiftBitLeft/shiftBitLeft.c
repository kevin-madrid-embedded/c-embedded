#include<stdio.h>
#include"shiftBitLeft.h"

unsigned char shiftBitLeft(unsigned char byte, unsigned char shift){
    if(shift > 7)
        return byte;
    return byte << shift;
}
