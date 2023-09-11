#include <stdio.h>

int check(unsigned long x) {
    unsigned long i = x / 2;
    while(i >= 2) {
        if(x % i == 0) {
            i = 0;
        } else {
            i--;
        }
    } 
    if (i == 1) {
        return 1;
    } 
    return 0;
}

int main() {
    unsigned long x = 0;
    scanf("%lu", &x);
    if(x < 2) {
        printf("exception: menshe 2\n");
    } else {
        for(unsigned long i = 0; i <= x; i++) {
            if(check(i)) {
                printf("%lu ", i);
            }
        }
    }
}
