#include <stdio.h>
#include <stdlib.h>

int** createArray(size_t size) {
    int** arr;
    arr = malloc(sizeof(int*) * size);
    for(size_t i = 0; i < size; i++) {
        arr[i] = malloc(sizeof(int) * (i + 1));
    }
    return arr;
}

unsigned int binom(int n, int k) {
    if(k > n / 2) k = n - k;
    if(k == 1) return n;
    if(k == 0) return 1;
    return binom(n - 1, k) + binom(n - 1, k - 1);
}

int main() {
    int x = 0;
    scanf("%d", &x);
    if(x < 1) {
        printf(">1 only");
        exit(0);
    }
    /* for(int i = 0; i < 4; i++) { */
    /*     for(int j = 0; j < i + 1; j++) { */
    /*         printf("%d ", binom(i, j)); */
    /*     } */
    /*     printf("\n"); */
    /* }  */
    /* int** arr; */
    /* arr = malloc(sizeof(int*) * n); */
    /* for(int i = 0; i < n; i++) { */
    /*     arr[i] = malloc(sizeof(int) * (i + 1)); */
    /* } */
    /* for(int i = 0; i < n; i++) { */
    /*     for(int j = 0; j < i + 1; j++) { */
    /*         arr[i][j] = j; */
    /*     } */
    /* } */
    /* for(int i = 0; i < n; i++) { */
    /*     for(int j = 0; j < i + 1; j++) { */
    /*         printf("%d ", arr[i][j]); */
    /*     } */
    /*     printf("\n"); */
    /* } */
}
