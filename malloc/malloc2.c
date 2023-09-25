#include <stdio.h>
#include <stdlib.h>

void nullCheck(void* ptr) {
    if(ptr == NULL) {
        printf("not enough memory");
        exit(0);
    }
}

void allocateArr(int** arr, int n) {
    *arr = malloc(sizeof(int) * n);
    nullCheck(*arr);
}


int scanArr(int* arr, int n) {
    size_t i = 0;
    while(i < n) {
        scanf("%d", &arr[i]);
        if(arr[i] == 0) {
            return 1;
        }
        i++;
    }
    return 0;
}

void processArr(int* arr, size_t n) {
    if(arr == NULL) {
        allocateArr(&arr, n);
    } else {
        int* new_arr;
        allocateArr(&new_arr, n);
        for(int i = 0; i < n / 2; i++) {
            new_arr[i] = arr[i];
        }
        free(arr);
        arr = new_arr;
    }
    if(scanArr(arr, n)) {
        free(arr);
        return;
    } else {
        processArr(arr, n * 2);
    }
}

int main() {
    int* arr = NULL;
    processArr(arr, 2);
}
