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

// problem 1
void scanArr(int* arr, int n) {
    for(size_t i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
}

// problem 2
void printArr(int* arr, int n) {
    for(size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// problem 3
void revertArray(int* arr, int n) {
    for(size_t i = 0; i < n / 2; i++) {
        swap(&arr[i], &arr[n - i - 1]);
    }
}

// problem 4
int maxInArray(int *arr, int n) {
    int max = arr[0];
    for(size_t i = 1; i < n; i++) {
        if(arr[i] > max) max = arr[i];
    }
    return max;
}

// problem 5
int findInArr(int* arr, int n, int x) {
    size_t i = 0;
    while(arr[i] != x && i < n) i++; 
    if(arr[i] == x) return i + 1;
    else return -1;
}

size_t numberOfDigits(int x) {
    size_t i = 1;
    if(x < 0) x *= -1;
    while(x > 9) {
        x /= 10;
        i++;
    }
    return i;
}

// problem 6
void extractDigits(int* arr, int x, int n) {
    size_t xSize = numberOfDigits(x);      
    if(xSize > n) xSize = xSize - (xSize - n); 
    if(x == 0) {
        arr[0] = x;
        return;
    }
    for(size_t i = xSize; i > 0; i--) {
        arr[i - 1] = x % 10;
        x /= 10;
    }
}

// problem 7
int compareArrays(int* arr1, int* arr2, int n1, int n2) {
    size_t iter = n1 < n2 ? n1 : n2;
    size_t i = 0;
    for(i = 0; i < iter; i++) {
        if(arr1[i] > arr2[i]) return 1;
        if(arr1[i] < arr2[i]) return -1;
    }
    if(n1 < n2) return -1;
    if(n1 > n2) return 1;
    return 0;
}

// tests for problem 7
void compareArraysTest(int* arr1, int* arr2, int i) {
    printf("[Test for compareArrays] 0 == %d\n", compareArrays(arr1, arr2, i, i));
    arr1[i + 1] = i + 1;
    printf("[Test for compareArrays] 1 == %d\n", compareArrays(arr1, arr2, i + 1, i));
    arr2[i + 1] = i + 1;
    arr2[i + 2] = i + 2;
    printf("[Test for compareArrays] -1 == %d\n", compareArrays(arr1, arr2, i + 1, i + 2));
}

void initArray(int* arr, int n) {
    for(size_t i = 0; i < n; i++) {
        arr[i] = i;
    }
}

int main() {
    size_t size = 0;
    scanf("%lu", &size);
    int* arr; 
    allocateArr(&arr, size);

    scanArr(arr, size);
    printArr(arr, size);

    printf("Reverted array:\n");
    revertArray(arr, size);
    printArr(arr, size);

    printf("search number:\n");
    int x = 0;
    scanf("%d", &x);
    printf("number spot(-1 if not found): %d\n", findInArr(arr, size, x));

    int extract = 0;
    printf("enter number for extractDigits:\n");
    scanf("%d", &extract);
    int* extractArr;
    allocateArr(&extractArr, 10);
    initArray(extractArr, 10);
    extractDigits(extractArr, extract, 10);
    printArr(extractArr, 10);


    int* arr1;
    int* arr2;

    allocateArr(&arr1, 20);
    allocateArr(&arr2, 20);
    initArray(arr1, 10);
    initArray(arr2, 10);

    compareArraysTest(arr1, arr2, 10);

    free(arr);
    free(extractArr);
    free(arr1);
    free(arr2);
}
