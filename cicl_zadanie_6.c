#include <stdio.h>
#include <assert.h>

short numberLength(unsigned long x) {
    short i = 0;
    if (x == 0) return 1;
    while (x > 0) {
        i++;
        x /= 10;
    }
    return i;
}

short first_3_sum(unsigned long x) {
    short sum = 0;
    for(int i = 0; i < 3; i++) {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

short second_3_sum(unsigned long x) {
    x = x / 1000;
    return first_3_sum(x);
}

int main() {
    unsigned long x = 0, y = 0;
    scanf("%lu", &x);
    scanf("%lu", &y);
    assert(x < y);
    for (unsigned long i = x; i <= y; i++) {
        if(numberLength(i) == 6) {
            if(first_3_sum(i) == second_3_sum(i))
                printf("%lu ", i);
        }
    } 
}
