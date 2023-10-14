#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int palindrom(const char* str, size_t n) {
    size_t left = 0, right = n - 1;
    while(left < right) {
        if(str[left] == ' ') {
            left++;
            continue;
        }
        if(str[right] == ' ') {
            right--;
            continue;
        }
        if(!(str[left] == str[right])) {
            return 0;
        } 
        left++;
        right--;
    }
    return 1;
}

void tests() {
    assert(palindrom("asdqwe", 6) == 0);
    assert(palindrom("asdasd", 6) == 0);
    assert(palindrom("asddsa", 6) == 1);
    assert(palindrom("asd qwe", 7) == 0);
    assert(palindrom("asdddsa", 7) == 1);
    assert(palindrom("asddds a", 8) == 1);
    assert(palindrom("a sdddsa", 8) == 1);
    assert(palindrom("a s d ddsa", 10) == 1);
    assert(palindrom("a s d ddsa", 10) == 1);
    assert(palindrom("a s d d d s a", 13) == 1);
    assert(palindrom("a s d sd d s a", 14) == 0);
    assert(palindrom("a s d da d s a", 14) == 0);
    assert(palindrom("asdqwe", 6) == 0);
}

int main() {
    tests();
}
