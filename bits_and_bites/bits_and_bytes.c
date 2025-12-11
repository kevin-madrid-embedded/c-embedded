#include"printb/printb.h"
#include"shiftBitRight/shiftBitRight.h"
#include"shiftBitLeft/shiftBitLeft.h"
#include"setBitMask/setBitMask.h"
#include"clearBitMask/clearBitMask.h"
#include"toggleBitMask/toggleBitMask.h"
#include"setBit/setBit.h"
#include"getBit/getBit.h"

int main(){
    unsigned char test = 0x80;
    unsigned char mask = 0x00;
#ifdef TESTALL
    printf("Print test value:\n");
    printb(test);
    printf("Print shift bit right test value:\n");
    printb(shiftBitRight(test, 3));
    printf("Print shift bit left test value:\n");
    printb(shiftBitLeft(test, 4));
    printf("Set bits according to Mask: 0x%x\n",mask);
    printb(setBitMask(test,mask));
    printf("Clear bits according to Mask: 0x%x\n",mask);
    printb(clearBitMask(test,mask));
    printf("Toggle bits according to Mask: 0x%x\n",mask);
    printb(toggleBitMask(test,mask));
    printf("Set bit 2 of value: 0x%x\n",test);
    printb(setBit(test,2));
#endif
    test = 0xAA;
    for(unsigned char bit = 0x02; bit < 8; bit++){
        printf("Get bit %d value of byte: 0x%x\n",bit,test);
        printb(getBit(test,bit));
    }
    return 0;
}
