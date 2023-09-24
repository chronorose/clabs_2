#include <stdio.h>
#include <stddef.h>

void infinite_recursion(char* start, char* current) {
    char v;
    current = &v;
    ptrdiff_t result = start - current;
    printf("%td\n", result / 1024);
    infinite_recursion(start, current);
}

int main() {
    char start;
    infinite_recursion(&start, NULL);
}
