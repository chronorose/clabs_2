#include <stdio.h>
#include <stdlib.h>

void nullCheck(void* ptr) {
    if(ptr == NULL) {
        printf("not enough memory");
        exit(0);
    }
}

void allocateArr(int** ptr, size_t n) {
    *ptr = malloc(sizeof(int));
    nullCheck(*ptr);
}

int* concat(int* ptr1, int* ptr2, size_t n1, size_t n2) {
    size_t full_size = n1 + n2;
    int* new_array = malloc(sizeof(int) * full_size);
    for(size_t i = 0; i < n1 + n2; i++) {
        if(i < n1) new_array[i] = ptr1[i];
        if(i > n1) new_array[i] = ptr2[i - n1];
    }
    return new_array;
}

int* initArray(int n) {
    int* arr;
    allocateArr(&arr, n);
    for(int i = 0; i < n; i++) arr[i] = i;
    return arr;
}

void printArr(int* arr, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n1 = 5;
    int n2 = 5;
    int* arr1 = initArray(n1);
    printArr(arr1, n1);
    int* arr2 = initArray(n2);
    printArr(arr2, n2);
    int* arr3 = concat(arr1, arr2, n1, n2);
    printArr(arr3, n1 + n2);
}
