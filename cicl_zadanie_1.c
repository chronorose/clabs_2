#include <stdio.h>

int main() {
    unsigned long x = 0;
    scanf("%lu", &x);
    for(size_t i = 0; i <= x; i++) {
        int c = 0;
        if(i % 3 == 0) {
            printf("fizz");
            c++;
        } 
        if(i % 5 == 0) {
            printf("buzz");
            c++;
        }
        if (c == 0) {
            printf("%lu ", i);
        } else {
            printf(" ");
        }
    }
}
