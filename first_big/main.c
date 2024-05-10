#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARRAY_SIZE 8
#define STRING_SIZE 8

typedef struct {
    char* str;
    size_t len;
    size_t cap;
} String;

typedef struct {
    String** val;
    size_t len;
    size_t cap;
} Array;

typedef struct {
    size_t parentheses;
    size_t number;
    size_t math;
    size_t glue;
    unsigned char parenCheck;
    unsigned char numberCheck;
    unsigned char mathCheck;
    unsigned char glueCheck;
    unsigned char spaces;
    unsigned char newlines;
    unsigned char word;
    unsigned char change;
} State;

typedef struct {
    FILE* input;
    FILE* output;
} Files;

typedef enum {
    WORD,
    PM_WORD,
    WHITESPACE,
    NEW_LINE,
    DIVIDER,
    NUMBER,
    MATH,
} Type;

void nullCheck(void* ptr) {
    if (ptr == NULL) {
        printf("something went pretty wrong :)\n");
        exit(1);
    }
}

int isAlpha(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

int isWord(char ch) {
    return isAlpha(ch) || isDigit(ch);
}

int firstLetter(char ch) {
    return isWord(ch) || ch == '+' || ch == '-';
}

int isNewLine(char ch) {
    return ch == '\n';
}

int isMath(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int isWhiteSpace(char ch) {
    return ch == ' ' || ch == '\n';
}

size_t max(size_t first, size_t second) {
    return first > second ? first : second;
}

int isPalindrom(String* string) {
    size_t left = 0, right = string->len - 1;
    for (size_t i = 0; i <= right; i++) {
        if (!isAlpha(string->str[i])) return 0;
    }
    while (left < right) {
        if (string->str[left] == ' ') {
            left++;
            continue;
        }
        if (string->str[right] == ' ') {
            right--;
            continue;
        }
        if (string->str[left] != string->str[right]) {
            return 0;
        }
        left++;
        right--;
    }
    return 1;
}

Array* initArray() {
    Array* array = malloc(sizeof(Array));
    nullCheck(array);
    array->cap = ARRAY_SIZE;
    array->len = 0;
    array->val = malloc(sizeof(String*) * array->cap);
    nullCheck(array->val);
    return array;
}

String* initString() {
    String* string = malloc(sizeof(String));
    nullCheck(string);
    string->cap = STRING_SIZE;
    string->len = 0;
    string->str = malloc(sizeof(char) * string->cap);
    nullCheck(string->str);
    return string;
}

void ensureSizeArray(Array* array) {
    if (array->len + 1 >= array->cap) {
        array->cap *= 2;
        array->val = realloc(array->val, sizeof(String*) * array->cap);
        nullCheck(array->val);
    }
}

void ensureSizeString(String* string) {
    if (string->len + 1 >= string->cap) {
        string->cap *= 2;
        string->str = realloc(string->str, sizeof(char) * string->cap);
        nullCheck(string->str);
    }
}

void append(Array* array, String* string) {
    ensureSizeArray(array);
    array->val[array->len++] = string;
}

void pushBack(String* string, char ch) {
    ensureSizeString(string);
    string->str[string->len++] = ch;
    string->str[string->len] = '\0';
}

void freeString(String* string) {
    free(string->str);
    free(string);
}

void freeArray(Array* array) {
    for (size_t i = 0; i < array->len; i++) {
        freeString(array->val[i]);
    }
    free(array->val);
    free(array);
}

void freeFiles(Files* files) {
    fclose(files->input);
    fclose(files->output);
    free(files);
}

FILE* getFileRead(char* path) {
    FILE* fptr = fopen(path, "r");
    nullCheck(fptr);
    return fptr;
}

FILE* getFileWrite(char* path) {
    FILE* fptr = fopen(path, "w");
    nullCheck(fptr);
    return fptr;
}

String* concatenate(String* str1, String* str2) {
    size_t cap = max(str1->cap, str2->cap);
    size_t len = str1->len + str2->len;
    if (len > cap) cap *= 2;
    str1->len = len;
    str1->cap = cap;
    str1->str = realloc(str1->str, sizeof(char) * str1->cap);
    str1->str = strcat(str1->str, str2->str);
    return str1;
}

void delete(Array* array, size_t index) {
    if (index >= array->len) return;
    freeString(array->val[index]);
    for (size_t i = index; i < array->len; i++) {
        array->val[i] = array->val[i + 1];
    }
    array->len--;
}

void getArray(Array* array, Files* files) {
    unsigned char word = 0;
    char ch = fgetc(files->input);
    while (!feof(files->input)) {
        if (word) {
            if (isWord(ch)) {
                pushBack(array->val[array->len - 1], ch);
            } else {
                if (firstLetter(ch)) {
                    word = 1;
                } else {
                    word = 0;
                }
                String* str = initString();
                pushBack(str, ch);
                append(array, str);
            }
         } else {
            String* str = initString();
            pushBack(str, ch);
            append(array, str);
            if (firstLetter(ch)) {
                word = 1;
            }
        }
        ch = fgetc(files->input);
    }
}

int times(int number, size_t times) {
    int holder = number;
    for (size_t i = 0; i < times; i++) {
        number *= holder;
    }
    return number;
}

size_t nLen(int number) {
    size_t size = 0;
    do {
        number /= 10;
        size++;
    } while (number != 0);
    return size;
}

String* clearString(String* string) {
    free(string->str);
    string->len = 0;
    string->cap = STRING_SIZE;
    string->str = malloc(sizeof(char) * string->cap);
    nullCheck(string->str);
    return string;
}

String* toString(String* string, int number) {
    size_t size = nLen(number);
    string = clearString(string);
    for (size_t i = 0; i < size; i++) {
        int cur_num = (number / ((times(10, size - i - 1) / 10)) % 10);
        pushBack(string, (char)(cur_num + '0'));
    }
    return string;
}

void pushBackString(String* string, const char* str) {
    size_t size = strlen(str);
    for (size_t i = 0; i < size; i++) {
        pushBack(string, str[i]);
    }
}

String* stringWithString(String* string, const char* str) {
    string = clearString(string);
    pushBackString(string, str);
    return string;
}

int toNumber(String* string) {
    if (string->len > 9) return -1;
    int sum = 0;
    for (size_t i = 0; i < string->len; i++) {
        sum += ((int)(string->str[i] - '0')) * (times(10, (string->len - i - 1)) / 10);
    }
    return sum;
}

String* calculation(int first, int second, char op, String* string) {
    int result = 0;
    int errorCode = 0;
    switch (op) {
        case '+':
            result = first + second;
            break;
        case '-':
            result = first - second;
            break;
        case '*':
            result = first * second;
            break;
        case '/':
            if (second == 0) {
                errorCode = 1;
            } else {
                result = first / second;
            }
            break;
    }
    if (errorCode) {
        string = clearString(string);
        stringWithString(string, "ERROR");
    } else {
        string = toString(string, result);
    }
    return string;
}

Type checkType(String* string) {
    int number = 1;
    char fLetter = string->str[0];
    if (firstLetter(fLetter)) {
        for (size_t i = 0; i < string->len; i++) {
            if (!isDigit(string->str[i])) number = 0;
        }
        if (number) return NUMBER;
        if (isMath(fLetter) && string->len == 1) return MATH;
        if (isMath(fLetter)) return PM_WORD;
        return WORD;
    }
    if (isMath(fLetter)) return MATH;
    if (isNewLine(fLetter)) return NEW_LINE;
    if (isWhiteSpace(fLetter)) return WHITESPACE;
    return DIVIDER;
}

void initState(State* state) {
    state->change = 0;
    state->spaces = 0;
    state->newlines = 0;
    state->word = 0;
    state->parentheses = 0;
    state->math = 0;
    state->number = 0;
    state->glue = 0;
    state->parenCheck = 0;
    state->glueCheck = 0;
    state->mathCheck = 0;
    state->numberCheck = 0;
}

void zeroState(State* state) {
    state->newlines = 0;
    state->spaces = 0;
    state->number = 0;
    state->numberCheck = 0;
    state->math = 0;
    state->mathCheck = 0;
    state->glue = 0;
    state->glueCheck = 0;
}

void processArray(Array* array) {
    State state;
    do {
        initState(&state);
        for (size_t i = 0; i < array->len; i++) {
            Type type = checkType(array->val[i]);
            switch (type) {
                case NEW_LINE:
                    if (i == 0) {
                        delete(array, i--);
                        state.newlines++;
                        state.change = 1;
                        break;
                    }
                    if (state.newlines > 1) {
                        delete(array, i--);
                        state.change = 1;
                        state.newlines++;
                        break;
                    }
                    state.newlines++;
                    state.glueCheck = 0;
                    break;
                case WHITESPACE:
                    if (i == 0 || i == array->len - 1) {
                        delete(array, i--);
                        state.change = 1;
                        state.spaces++;
                        break;
                    }
                    if (state.spaces > 0 || state.newlines > 0) {
                        delete(array, i--);
                        state.change = 1;
                        state.spaces++;
                        break;
                    }
                    state.spaces++;
                    state.glueCheck = 0;
                    break;
                case DIVIDER:
                    if (array->val[i]->str[0] == '(') {
                        state.parentheses = i;
                        state.parenCheck = 1;
                    }
                    if (array->val[i]->str[0] == ')' && state.parenCheck && state.word == 1) {
                        delete(array, state.parentheses);
                        state.change = 1;
                        i--;
                        delete(array, i--);
                        state.word = 0;
                        state.parenCheck = 0;
                    }
                    state.word = 0;
                    zeroState(&state);
                    break;
                case WORD:
                    if (!state.glueCheck) {
                        if (isPalindrom(array->val[i])) {
                            stringWithString(array->val[i], "PALINDROM");
                            state.change = 1;
                        }
                    } else {
                        String* stringForCheck = initString();
                        stringForCheck->str[0] = '\0';
                        for (size_t j = state.glue; j <= i; j++) {
                            stringForCheck = concatenate(stringForCheck, array->val[j]);
                        }
                        if (isPalindrom(stringForCheck)) {
                            stringWithString(array->val[state.glue], "PALINDROM");
                            for (size_t j = state.glue + 1; j <= i;) {
                                delete(array, j);
                                i--;
                            }
                            state.change = 1;
                        }
                        freeString(stringForCheck);
                    }
                    if (state.parenCheck && !state.glueCheck) {
                        state.word++;
                    }
                    if (!state.glueCheck && ((state.parenCheck && state.word == 1) || !state.parenCheck)) {
                        state.glue = i;
                        state.glueCheck = 1;
                    }
                    size_t oldGlue = state.glue;
                    unsigned char oldGlueCheck = state.glueCheck;
                    zeroState(&state);
                    state.glue = oldGlue;
                    state.glueCheck = oldGlueCheck;
                    break;
                case PM_WORD:
                    if (state.parenCheck) state.word++;
                    zeroState(&state);
                    break;
                case NUMBER:
                    if (!state.numberCheck) {
                        state.number = i;
                        state.numberCheck = 1;
                        state.mathCheck = 0;
                    } else if (state.mathCheck == 1) {
                        int firstNumber = toNumber(array->val[state.number]);
                        int secondNumber = toNumber(array->val[i]);
                        char op = array->val[state.math]->str[0];
                        array->val[state.number] = calculation(firstNumber, secondNumber, op, array->val[state.number]);
                        for (size_t j = state.number + 1; j <= i;) {
                            delete(array, j);
                            i--;
                        }
                        state.numberCheck = 0;
                        state.change = 1;
                    }
                    if (state.parenCheck) state.word++;
                    else state.word = 0;
                    size_t oldNumber = state.number;
                    unsigned char oldNumberCheck = state.numberCheck;
                    zeroState(&state);
                    state.numberCheck = oldNumberCheck;
                    state.number = oldNumber;
                    break;
                case MATH:
                    state.spaces = 0;
                    state.word = 0;
                    state.newlines = 0;
                    state.glueCheck = 0;
                    if (state.mathCheck) {
                        state.mathCheck++;
                    } else if (state.numberCheck) {
                        state.math = i;
                        state.mathCheck++;
                    }
            }
        }
    } while (state.change != 0);
}

void writeToFile(Array* array, Files* files) {
    for (size_t i = 0; i < array->len; i++) {
        fprintf(files->output, "%s", array->val[i]->str);
    }
}

Files* initFiles(char* argv[]) {
    Files* files = malloc(sizeof(Files));
    nullCheck(files);
    files->input = getFileRead(argv[1]);
    files->output = getFileWrite(argv[2]);
    return files;
}

int main(int argc, char* argv[]) {
    Array* arr = initArray();
    Files* files = initFiles(argv);
    getArray(arr, files);
    processArray(arr);
    writeToFile(arr, files);
    freeArray(arr);
    freeFiles(files);
}
