#include<stdio.h>
#include"shiftBitRight.h"

unsigned char shiftBitRight(unsigned char byte, unsigned char shift){
    
    if(shift > 7)
        return byte;
    return byte >> shift;
}

