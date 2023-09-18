#include <stdio.h>

unsigned long gcd (unsigned long first, unsigned long second) {
    if(first == 0) {
        return second;
    }
    return gcd(second % first, first);
}

int main() {
    unsigned long x = 0;
    unsigned long y = 0;
    scanf("%lu", &x);
    scanf("%lu", &y);
    printf("%lu", gcd(x, y));
}
