#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define STR_SIZE 8 
#define DYN_SIZE 8 


typedef struct {
    char* str;
    size_t capacity;
    size_t size;
} String;

typedef struct {
    String** strs;
    size_t capacity;
    size_t size;
} Dyn;

void nullCheck(void* ptr) {
    if(ptr == NULL) {
        printf("something went pretty wrong hehe");
        exit(0);
    }
}

String* str_init() {
    String* str = malloc(sizeof(String));
    nullCheck(str);
    str->capacity = STR_SIZE;
    str->size = 0;
    str->str = malloc(sizeof(char*) * str->capacity); 
    nullCheck(str->str);
    return str;
}

Dyn* dyn_init() {
    Dyn* dyn = malloc(sizeof(Dyn));
    nullCheck(dyn);
    dyn->capacity = DYN_SIZE;
    dyn->size = 0;
    dyn->strs = malloc(sizeof(String*) * DYN_SIZE);
    nullCheck(dyn->strs);
    for(size_t i = 0; i < dyn->capacity; i++) {
        dyn->strs[i] = str_init(); 
    }
    return dyn;
}

void ensure_capacity_str(String* str) {
    if(str->size + 2 < str->capacity) return;
    str->capacity = str->capacity * 2;
    str->str = realloc(str->str, str->capacity * sizeof(char));
    nullCheck(str->str);
}

void str_push(String* str, const char ch) {
    ensure_capacity_str(str);
    str->str[str->size] = ch;
    str->size++;
}

void ensure_capacity_dyn(Dyn* dyn) {
    if(dyn->size + 1 < dyn->capacity) return;
    size_t old_cap = dyn->capacity;
    dyn->capacity = dyn->capacity * 2;
    dyn->strs = realloc(dyn->strs, dyn->capacity * sizeof(String*));
    nullCheck(dyn->strs);
    for(size_t i = old_cap; i < dyn->capacity; i++) {
        dyn->strs[i] = str_init();
    }
}

void push_back(Dyn* dyn, String* str) {
    ensure_capacity_dyn(dyn);
    dyn->strs[dyn->size++] = str;
}

Dyn* split(const char* str, size_t n) {
    Dyn* dyn = dyn_init();
    int stcounter = 0;
    String* string = dyn->strs[dyn->size];
    for(size_t i = 0; i < n; i++) {
        if(str[i] == ' ') {
            stcounter = 0;
            if(string->size == 0) continue;
            str_push(string, '\0');
            push_back(dyn, string);
            string = dyn->strs[dyn->size];
            continue;
        }
        if(!stcounter) {
            str_push(string, str[i]);
            stcounter = 1;
            continue;
        }
        if(stcounter) {
            str_push(string, str[i]); 
        }
    }
    if(stcounter) push_back(dyn, string);
    return dyn;
}

int main() {
    char* a = " asd qwe a a asd qwe lasd qwe sddd asdqwe sa asd sad dqwe sdsa  wqe qwee qwe 12 23 123 441 2";
    char* b = " asd qwe";
    Dyn* dyn = split(a, strlen(a));
    printf("string=%s\n", a);
    for(size_t i = 0; i < dyn->size; i++) {
        printf("%ld ", strlen(dyn->strs[i]->str));
        printf("%s\n", dyn->strs[i]->str);
    }
    for(size_t i = 0; i < dyn->capacity; i++) {
        free(dyn->strs[i]->str);
        free(dyn->strs[i]);
    }
    free(dyn->strs);
    free(dyn);
}
