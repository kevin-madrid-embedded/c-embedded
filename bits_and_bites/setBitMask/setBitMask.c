#include<stdio.h>
#include"setBitMask.h"

unsigned char setBitMask(unsigned char byte, unsigned char mask){
    return byte | mask;
}
