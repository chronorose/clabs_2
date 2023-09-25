#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

void infinite_recursion(char* start) {
    char v;
    char* current = &v;
    ptrdiff_t result = start - current;
    printf("%td\n", result / 1024);
    infinite_recursion(start);
}

int main() {
    char start;
    infinite_recursion(&start);
}
