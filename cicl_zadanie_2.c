#include <stdio.h> 

int main() {
    unsigned long x = 0;
    scanf("%lu", &x);
    for(size_t i = 0; i < x; i++) {
        for(size_t j = x * i; j < x * (i + 1); j++) {
            printf("%lu ", j); 
        }
        printf("\n");
    }
}
