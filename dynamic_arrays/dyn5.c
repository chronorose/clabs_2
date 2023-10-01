#include <stdio.h>
#include <stdlib.h>

void nullCheck(void* ptr) {
    if(ptr == NULL) {
        printf("not enough memory");
        exit(0);
    }
}

void scanArr(int** arr, size_t* size, size_t* capacity) {
    if(*capacity == 0) {
        *capacity = 8;
        *arr = realloc(*arr, sizeof(int) * (*capacity)); 
        nullCheck(*arr);
    }
    do {
        if(*size == *capacity - 1) {
            *capacity = *capacity * 2;
            *arr = realloc(*arr, sizeof(int) * (*capacity));
            nullCheck(*arr);
        }
        (*size)++;
        scanf("%d", &((*arr)[*size - 1]));
    } while(((*arr)[*size - 1]) != 0);
}

void printArr(int* arr, int size) {
    for(size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
} 

int main() {
    int* arr = NULL;
    size_t size = 0;
    size_t capacity = 0;
    scanArr(&arr, &size, &capacity);
    printArr(arr, size);
    free(arr);
}
