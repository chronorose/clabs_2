#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <setjmp.h>
#include <math.h>
#define OVERFLOW 1
#define WRONG_CHAR 2

int check_char(char ch, int* number, size_t base) {
    if(ch >= '0' && ch <= '9') {
        *number = (int)(ch - '0');
        return 1;
    }
    if(ch >= 'A' && ch <= 'F' && (ch - 55) < base) {
        *number = (int)(ch - 55);
        return 1;
    }
    return 0;
}

int ret_number(char ch, size_t base, jmp_buf* state) {
    int digit;
    int check = check_char(ch, &digit, base); 
    if(!check) {
        longjmp(*state, WRONG_CHAR);
    }
    return digit;
}

void check_for_overflow(int digit, int number, jmp_buf* state) {
    if(digit > INT_MAX - number) longjmp(*state, OVERFLOW);
}
// 101 
int s2i(const char* str, size_t base, jmp_buf* state) {
    if(base > 16 || base < 2) {
        printf("wrong base hehe");
        exit(0);
    } 
    int sign = str[0] == '-' ? 1 : 0;
    int full_number = 0;
    int digit = 0;
    size_t size = strlen(str);
    for(size_t i = sign; i < size; i++) {
        digit = ret_number(str[i], base, state);
        digit = digit * pow(base, size - i - 1);
        check_for_overflow(digit, full_number, state);
        full_number += digit;
    }
    return sign ? full_number * -1 : full_number;
}

void test() {
    jmp_buf state;
    int statev = setjmp(state);
    if(!statev) {
        char* a = "-12A";
        int ans = s2i(a, 16, &state);
        printf("%d\n", ans);
    } else if(statev == OVERFLOW) {
        printf("something got overflown oopsie");
    } else if(statev == WRONG_CHAR) {
        printf("input is wrong somewhere");
    }
}

int main() {
    test(); 
    return 0;
}
