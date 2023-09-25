#include <stdio.h>

int check(unsigned long x) {
    size_t n = x / 2;
    size_t i = 2;
    short temp = 0;
    while(i <= n) {
        if(x % i == 0) {
            return 1;
        }
        i++;
    }
    return 0;
}

int main() {
    unsigned long x = 0;
    scanf("%lu", &x);
    if(x < 2) {
        printf("error; x < 2");
        return 1;
    }
    for(size_t i = 2; i <= x; i++) {
        if(!check(i)) {
            printf("%lu ", i);
        }
    }
}
