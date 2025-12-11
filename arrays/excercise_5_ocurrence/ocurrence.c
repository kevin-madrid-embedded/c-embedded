#include<stdio.h>

unsigned int ocurrenceArray(unsigned char *array, size_t size, unsigned char num){
    if((array == NULL)||(size <= 0)) return 0;

    unsigned int ocurrence = 0;
    for(size_t index = 0; index < size; index++){
        if (array[index] == num){
	    ocurrence++;
	}
    }
    return ocurrence;
}
int main(){

    unsigned char array [] = {3,5,7,2,1,8,9};
    size_t size = sizeof(array)/sizeof(array[0]);
    unsigned int ocurrence = 7;
    printf("The ocurrence of num= %d is, %d",ocurrence,ocurrenceArray(array, size, ocurrence));

    return 0;
}
