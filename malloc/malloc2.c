#include <stdio.h>
#include <stdlib.h>

void nullCheck(void* ptr) {
    if(ptr == NULL) {
        printf("not enough memory");
        exit(0);
    }
}

void allocateArr(int** arr, size_t n) {
    *arr = malloc(sizeof(int) * n);
    nullCheck(*arr);
}


size_t scanArr(int* arr, size_t* n, size_t capacity) {
    size_t i = *n;
    while(i < capacity) {
        scanf("%d", &arr[i]);
        if(arr[i] == 0) {
            *n = i;
            return 1;
        }
        i++;
    }
    *n = i;
    return 0;
}

void printArr(int* arr, int n) {
    for(size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int* processArr(size_t* n, size_t* cap) {
    int* arr;
    allocateArr(&arr, *cap);
    while(1) {
        if(scanArr(arr, n, *cap)) {
            return arr;
        } 
        *cap *= 2;
        int* new_arr;
        allocateArr(&new_arr, *cap);
        for(size_t i = 0; i < *cap / 2; i++) {
            new_arr[i] = arr[i];
        }
        free(arr);
        arr = new_arr;
    }
}

int main() {
    size_t cap = 1;
    size_t n = 0;
    int* arr = processArr(&n, &cap);
    printArr(arr, n);
    free(arr);
}
