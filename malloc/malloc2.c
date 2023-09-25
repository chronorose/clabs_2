#include <stdio.h>
#include <stdlib.h>

void allocateArr(int** arr, int n) {
    *arr = malloc(sizeof(int) * n);
}

int main() {
    int* arr;
}
