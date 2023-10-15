#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define STR_SIZE 8 
#define DYN_SIZE 8 

void nullCheck(void* ptr) {
    if(ptr == NULL) {
        printf("something went pretty wrong hehe");
        exit(0);
    }
}

char* trim(const char* str, size_t n) {
    size_t real_size = 0;
    size_t start = 0, i = 0, end = 0, j = n - 1;
    char* new_string = malloc(sizeof(char) * n);
    nullCheck(new_string);
    do {
        if(str[i] == ' ') {
            i++;
            continue;
        }
        start = 1;
    } while(!start);
    do {
       if(str[j] == ' ') {
           j--;
           continue;
       } 
       end = 1;
    } while(!end);
    for(; i <= j; i++, real_size++) {
        new_string[real_size] = str[i];
    }
    new_string = realloc(new_string, real_size);
    nullCheck(new_string);
    return new_string;
}

int main() {
    char* a = "   asdqwe   "; 
    char* b = "   a sdqwe   "; 
    char* c = trim(a, strlen(a));
    char* d = trim(b, strlen(b));
    printf("string = %s; len = %ld;\n", c, strlen(c));
    printf("string = %s; len = %ld;\n", d, strlen(d));
    free(c);
    free(d);
}
