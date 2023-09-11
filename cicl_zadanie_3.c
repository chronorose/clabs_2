#include <stdio.h> 

// 1
// 2 3
// 4 5 6
// 7 8 9 10
// 11 12 13
// 5 * (6) / 2 - 1

int main() {
    unsigned long x = 0;
    scanf("%lu", &x);
    int count = 0;
    unsigned long sc = (x * (x + 1)) / 2 - 1;
    for(unsigned long i = 0; i <= sc;) {
        if(i + count > sc) {
            count = sc - i;
        }
        for(int j = 0; j <= count; j++) {
            printf("%lu ", i + j);
        }
        printf("\n");
        count++;
        i += count;
    }
}
