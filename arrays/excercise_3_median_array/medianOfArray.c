#include<stdio.h>
/*
*3.- Write a C program to calculate median of an array. In this C program, we are going to learn how to find the median of an array?* Here, we are reading N elements and finding their median element.
*/



void printArray(unsigned char*array, size_t size){
    if(array==NULL)return;
    if(size == 0)return;

    for(size_t i = 0; i<size ; i++){
        printf("%d",array[i]);
    }
    printf("\n");
}

void sortArray(unsigned char *arr, size_t size){
    
    if(arr==NULL)return ;
    if(size == 0)return ;

    unsigned char sorted = 0;
    unsigned char temp = 0;
    while (sorted != 1){
        sorted = 1; 
        for(size_t i = size-1; i > 0; i--){
            if(arr[i] < arr[i-1]){
                temp = arr[i-1];
                arr[i-1]=arr[i];
                arr[i]= temp;
                sorted = 0;
            }
        }
    }
}
unsigned int calculateMedian(unsigned char *array, size_t size){
    if((array==NULL)||(size==0)) return 0;
    unsigned char sorted = 0;
    unsigned int median = 0;
    while(sorted != 1){
        sorted = 1;
        for(int i = size -1; i>0; i--){
            if(array[i]< array[i-1]){
                sorted=0;
                break;
            }
        }
    }
    if (sorted ==0)
        return 0;
    if(size%2==0){
        median = (array[size/2]+array[(size/2)+1]/2);
    }
    else{
        median = array[size/2];
    }
    return median;
} 
int main(){
    size_t size = 7;
    //unsigned char array[size];
    unsigned char array[]={1,5,3,7,4,6,8};
    sortArray(array,size);
    printArray(array,size);

    printf("%d",calculateMedian(array,size));
    return 0;
}
