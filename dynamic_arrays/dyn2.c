#include <stdio.h>
#include <stdlib.h>

void nullCheck(void* ptr) {
    if(ptr == NULL) {
        printf("not enough memory");
        exit(0);
    }
}

void allocateArr(int** ptr, size_t n) {
    *ptr = malloc(sizeof(int) * n);
    nullCheck(*ptr);
}

int* initArray(int n) {
    int* arr;
    allocateArr(&arr, n);
    for(size_t i = 0; i < n; i++) arr[i] = i;
    return arr;
}

void printArr(int* arr, int n) {
    for(size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int* findSubArr(int* arr1, int* arr2, int n1, int n2) {
    for(size_t i = 0; i < n1; i++) {
        size_t j = 0;
        int* mem = &arr1[i];
        while(i + j < n1 && arr1[i + j] == arr2[j] && j < n2) {
            if(j == n2 - 1 && arr1[i + j] == arr2[j]) return mem;
            j++; 
        }
    }
    return NULL;
}

int main() {
    int n1 = 10;
    int n2 = 3;
    int* arr1 = initArray(n1);
    int* arr2 = malloc(sizeof(int) * n2); 
    for(int i = 0; i < n2; i++) arr2[i] = i + 7;
    int* ptr = findSubArr(arr1, arr2, n1, n2);
    printArr(arr1, n1);
    printArr(arr2, n2);
    printf("%p\n", ptr);
}
