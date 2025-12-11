#include<stdio.h>


unsigned char x = 7;
unsigned char y = 5;
unsigned char z = 0;


int main(){

    z = x & y;
    // 00000101
    printf("AND 0x%x\n",z);

    z = x | y;
    // 00000111
    printf("OR  0x%x\n",z);

    z = x ^ y;
    // 00000010
    printf("XOR 0x%x\n",z);

    z = x << y;
    // 1100000 = 448
    printf("LEFT SHIFT 0x%x\n",z);
    printf("LEFT SHIFT %d\n",z);

    z = x >> y;
    // fffff000
    printf("LEFT SHIFT 0x%x\n",z);
    printf("LEFT SHIFT %d\n",z);

    return 0;
}
