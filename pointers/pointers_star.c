#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void infinite_recursion(ptrdiff_t size) {
    printf("%ld\n", size);
    return infinite_recursion(++size);
}

int main() {
    ptrdiff_t size = 0;
    infinite_recursion(size);
}
