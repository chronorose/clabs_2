#include <stdio.h>

int numdel (unsigned long x) {
    unsigned long n = x / 2;
    size_t i = 2;
    int counter = 1;
    while(i <= n) {
        if(x % i == 0) counter++;
        i++;
    }
    return counter;
}

int main() {
    unsigned long x = 0;
    scanf("%lu", &x);
    if(x == 0) {
        printf("error; x = 0");
        return 1;
    }
    printf("%d", numdel(x));
}
