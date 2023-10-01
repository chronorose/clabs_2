#include <stdio.h>
#include <stdlib.h>

void nullCheck(void* ptr) {
    if(ptr == NULL) {
        printf("not enough memory!");
        exit(0);
    }
}

int** createArray(int size) {
    int** arr;
    arr = malloc(sizeof(int*) * size);
    nullCheck(arr);
    for(size_t i = 0; i < size; i++) {
        arr[i] = malloc(sizeof(int) * (i + 1));
        nullCheck(arr[i]);
    }
    return arr;
}

size_t binom(size_t n, size_t k) {
    if(k > n / 2) k = n - k;
    if(k == 1) return n;
    if(k == 0) return 1;
    return binom(n - 1, k) + binom(n - 1, k - 1);
}

void fillArray(int** arr, int size) {
    for(size_t i = 0; i < size; i++) {
        for(size_t j = 0; j <= i; j++) {
            arr[i][j] = binom(i, j);
        }
    }
}

void printArr(int** arr, int size) {
    for(size_t i = 0; i < size; i++) {
        for(size_t j = 0; j <= i; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int x = 0;
    scanf("%d", &x);
    if(x < 1) {
        printf(">1 only");
        exit(0);
    }
    int** arr = createArray(x);
    fillArray(arr, x);
    printArr(arr, x);
    for(size_t i = 0; i < x; i++) {
        free(arr[i]);
    }
    free(arr);
}
