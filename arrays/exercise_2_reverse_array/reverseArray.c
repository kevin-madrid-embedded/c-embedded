/*
 *2.- Write a C program to swap first element with last, second to second last and so on (reversing elements). like, first element with last, second element with second last and so on... i.e. reversing the array elements
 * */
#include<stdio.h>

void reverse_array(unsigned char *array, unsigned char size){
    char temp = 0;
    if(array == NULL)
        return;
    if(size == 0)
	return;
    for (unsigned char index = 0; index < size/2 ; index ++){
        temp = array[index];
	array[index] = array[size -1 -index];
	array[size-1-index] = temp;
    }
}
void fill_array(unsigned char *array, unsigned char size){
    if(array == NULL)
	return;
    if(size == 0)
	return;
    for (unsigned char index = 0; index < size ; index ++){
	array[index] = index;
    }

}

int main(){
    unsigned char size = 5;
    unsigned char array[size];

    fill_array(array,size);

    for(unsigned char index = 0; index < size; index++){
        printf("%d",array[index]);
    }


    reverse_array(array,size);

    for(unsigned char index = 0; index < size; index++){
        printf("%d",array[index]);
    }
    printf("\n");
}


