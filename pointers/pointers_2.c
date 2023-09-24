#include <stdio.h>

void evilScanf(int* p0, int* p1, int* p2) {
    int p0holder = *p0;
    int p1holder = *p1;
    int p2holder = *p2;
    scanf("%d", p0);
    scanf("%d", p1);
    scanf("%d", p2);
    if(*p0 < 0) {
        *p2 = *p0 * *p1 * *p2 * p1holder * p2holder; 
        *p1 = p0holder;
    }
}

int main() {
    int a = 1, b = 1, c = 1; 
    evilScanf(&a, &b, &c);
    printf("P0 -> %d\nP1 -> %d\nP2 -> %d\n",a, b, c);
}
