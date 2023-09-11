#include <stdio.h>

int main() {
    unsigned long x = 0;
    scanf("%lu", &x);
    if(x < 2) {
        printf("exception: menshe 2\n");
    } else {
        unsigned long i = x / 2;
        while(i >= 2) {
            if(x % i == 0) {
                i = 0;
            } else {
                i--;
            }
        } 
        if(i == 1) {
            printf("prostoe\n");
        } else {
            printf("ne prostoe\n");
        }
    }
}
