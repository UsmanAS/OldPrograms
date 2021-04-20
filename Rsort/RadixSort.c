//Usman Siddiqui
//usiddi4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rsort.h"

int getMax(int* arr, int n){
    int mx = 0;
    int i;
    for (i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void grow(int** arr, int* size){
    int* temp = malloc(sizeof(int) * *size * 2);
    int i;
    for(i = 0; i < *size; i++)
	temp[i] = (*arr)[i];
    free((*arr));
    (*arr) = temp;
    *size *= 2;
}
 
void countSort(int* arr, int n, int divisor){
    int* output = malloc(sizeof(int) * n);
    int i;
    int* count = malloc(sizeof(int) * n);

    memset(count, 0, n*sizeof(int));
    for (i = 0; i < n; i++)
        count[ (arr[i]/divisor)%n ]++;
    for (i = 1; i < n; i++)
        count[i] += count[i - 1];
 
    for (i = n - 1; i >= 0; i--){
        output[count[ (arr[i]/divisor)%n ] - 1] = arr[i];
        count[ (arr[i]/divisor)%n ]--;
    }
 
    for (i = 0; i < n; i++)
        arr[i] = output[i];
    free(output);
    free(count);
}
 
void radixSort(int* arr, int n){
    int max = getMax(arr, n);
    int divisor;
    for (divisor = 1; max/divisor > 0; divisor *= n)
        countSort(arr, n, divisor);
}
 
void print(int* arr, int n){
    int i;
    printf("Contents of array: \n");
    for (i = 0; i < n; i++)
        printf("%d\n", arr[i]);
}

