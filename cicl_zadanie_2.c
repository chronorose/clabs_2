#include <stdio.h> 
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
