#include <stdio.h> 

// 1
// 2 3
// 4 5 6
// 7 8 9 10
// 11 12 13

int main() {
    unsigned long x = 0;
    scanf("%lu", &x);
    for(unsigned long i = 0; i < x; i++) {
        for(unsigned long j = x * i + 1; j <= x * (i + 1); j++) {
            printf("%lu ", j); 
        }
        printf("\n");
    }
}
