#include <stdio.h>
#include <stdlib.h>

int main() {
    int n = 5;
    int** arr;
    arr = malloc(sizeof(int*) * n);
    for(int i = 0; i < n; i++) {
        arr[i] = malloc(sizeof(int) * (i + 1));
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i + 1; j++) {
            arr[i][j] = j;
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i + 1; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}
