#include<stdio.h>
#include"clearBitMask.h"

unsigned char clearBitMask(unsigned char byte, unsigned char mask){
	return byte & ~mask;
}
