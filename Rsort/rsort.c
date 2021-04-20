#include <stdio.h>
#include <stdlib.h>
#include "rsort.h"

void main(){
    int size = 10;
    int* arr = malloc(sizeof(int) * size);
    int i = 0;
    int input = 1;
    while(input != EOF){
	printf("Enter a number:(-999 to quit) \n");
	scanf("%d", &input);
	if(input == -999)
		break;
	if(input > 0){
		if(i == size)
			grow(&arr, &size);
		arr[i] = input;
		i++;
	}
    }
    print(arr, i);
    radixSort(arr, i);
    print(arr, i);
    free(arr);
}