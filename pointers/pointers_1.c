#include <stdio.h>

void test() {
    int a;
    printf("%p\n", &a);
    a = 32;
    int b = 34;
    int c = 36;
}

void kek() {
    test();
}

int main() {
    test();
    kek();
}
