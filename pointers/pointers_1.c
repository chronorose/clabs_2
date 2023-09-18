#include <stdio.h>

void swap(int * a, int * b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int main() {
    int x = 0, y = 0;
    scanf("%d%d", &x, &y);
    swap(&x, &y);
    printf("x = %d; y = %d", x, y);
}
