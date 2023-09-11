#include <stdio.h> 

int main() {
    unsigned long x = 0;
    scanf("%lu", &x);
    int count = 0;
    if(x <= 0) printf("error");
    else {
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
}
