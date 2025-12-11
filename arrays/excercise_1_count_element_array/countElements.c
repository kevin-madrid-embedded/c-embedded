#include<stdio.h>

int main(){ 
    int array[20];
    printf("Array size is: %ld\n",sizeof(array)/sizeof(array[0]) );
}
