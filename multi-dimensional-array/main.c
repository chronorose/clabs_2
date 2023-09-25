#include <stdio.h>

void scanArr(int arr[4][4]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
}

void printArr(int arr[4][4]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            printf("%2d ", arr[i][j]);
        }
        printf("\n");
    }
}

void swap(int* arr1, int* arr2) {
    int temp = *arr1;
    *arr1 = *arr2;
    *arr2 = temp;
}

void reverseArr(int arr[4][4]) {
    int count = 0;
    int size = 4;
    for(int i = 0; i < size; i++) {
        for(int j = i + 1; j < size; j++) {
            swap(&arr[i][j], &arr[j][i]);
        }
    }
}

int main() {
    int arr[4][4];
    scanArr(arr);
    printArr(arr);
    printf("\n");
    reverseArr(arr);
    printArr(arr);
}
