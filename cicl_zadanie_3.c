#include <stdio.h> 
#include <assert.h>

int main() {
    unsigned long x = 0;
    long y = 0;
    scanf("%lu", &y);
    assert(y > 0);
    x = y;
    size_t count = 0;
    unsigned long sc = (x * (x + 1)) / 2 - 1;
    for(size_t i = 0; i <= sc;) {
        for(size_t j = 0; j <= count; j++) {
            printf("%lu ", i + j);
        }
        printf("\n");
        count++;
        i += count;
    }
}
