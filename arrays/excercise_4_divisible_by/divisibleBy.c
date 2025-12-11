#include<stdio.h>

unsigned int divisibleBy(unsigned char *arr, size_t size, unsigned char num){
    if (arr== NULL || size <= 0) return 0;

    size_t counter = 0;
    printf("Is divisible by =%d\n",num);
    for(size_t index = 0; index < size; index++){
        if(arr[index]%num == 0){
	    printf("%d,",arr[index]);
	    counter++;
	}
	printf("\n");
    }
    return counter;
}

int main(){
    unsigned char dividend = 3;
    unsigned char array[] = {4,2,1,0,3,6,9,10};
    size_t size = sizeof(array)/sizeof(array[0]);
    printf("Number of elements in Array divisible by:%d, is:%d",dividend,divisibleBy(array,size,dividend));
    return 0;
}
