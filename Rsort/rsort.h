int getMax(int* arr, int n);
// Gets the max value in the array arr, n being the size of the array

void grow(int** arr, int* size);
// Grows the array, arr, by double increasing size to be size*2

void countSort(int* arr, int n, int divisor);
// Helper function for Radix Sort, is called multiple times to do the actual sorting

void radixSort(int* arr, int n);
// Sets up parts to do RadixSort using countSort

void print(int* arr, int n);
// Prints the given array arr with its size being n
