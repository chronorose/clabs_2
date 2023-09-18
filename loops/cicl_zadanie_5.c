#include <stdio.h>
#include <assert.h>

int check(unsigned long x) {
    size_t i = x / 2;
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
    assert(x >= 2);
    for(size_t i = 0; i <= x; i++) {
        if(check(i)) {
            printf("%lu ", i);
        }
    }
}
