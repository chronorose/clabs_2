#include <stdio.h>

void _swap(int * a, int * b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void swap(int *pa, int *pb) {
    int c = *pa;
    *pa = *pb;
    *pb = c;
}

int main() {
    int x = 0, y = 0;
    scanf("%d%d", &x, &y);
    swap(&x, &y);
    printf("x = %d; y = %d\n", x, y);
}
