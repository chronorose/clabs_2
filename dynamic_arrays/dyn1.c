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

void concat(int* ptr1, int* ptr2, int**res_arr, size_t n1, size_t n2, size_t* res_n) {
    *res_n = n1 + n2;
    *res_arr  = malloc(sizeof(int) * (*res_n));
    nullCheck(*res_arr);
    for(size_t i = 0; i < n1 + n2; i++) {
        if(i < n1) (*res_arr)[i] = ptr1[i];
        if(i > n1) (*res_arr)[i] = ptr2[i - n1];
    }
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

int main() {
    size_t n1 = 8;
    size_t n2 = 5;
    int* arr1 = initArray(n1);
    printArr(arr1, n1);
    int* arr2 = initArray(n2);
    printArr(arr2, n2);
    int* arr3;
    size_t n_res;
    concat(arr1, arr2, &arr3, n1, n2, &n_res);
    printArr(arr3, n_res);
    free(arr1);
    free(arr2);
    free(arr3);
}
