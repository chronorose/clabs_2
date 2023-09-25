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

int* findSubArr(int* arr1, int* arr2, )

int main() {
    
}
