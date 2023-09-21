#include <stdio.h>

int* test() {
    /* int a; */
    /* unsigned int b; */
    /* long c; */
    /* char d; */
    /* printf("%p\n%p\n%p\n%p", &a, &b, &c, &d); */
    int *a = 0;
    return a;
}

int main() {
    int *a = test();
    int *b = test();
    if(a == b) {
        printf("same addres");
    } else {
        printf("not the same address");
    }
}
//blblblbl
