#include <stdio.h>

int main() {
    unsigned short x = 0;
    scanf("%hu", &x);
    if (x % 4 == 0) {
        if (x % 100 == 0 && x != 400) {
            printf("ne visokosniy\n");
        } else {
            printf("visokosniy\n");
        }
    }
}
