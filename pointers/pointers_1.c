#include <stdio.h>

void test() {
    int a = 32;
    printf("&a -> %p\n", &a);
}

void kek() {
    test();
}

int main() {
    test();
    kek();
}
