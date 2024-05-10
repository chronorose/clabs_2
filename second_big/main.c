#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARRAY_SIZE 8
#define STRING_SIZE 8

#define DYN_STRUCT(type, name)                                                                     \
    typedef struct {                                                                               \
        type val;                                                                                  \
        size_t len;                                                                                \
        size_t cap;                                                                                \
    } name

#define INIT_STRUCT(type, malloc_type, size)                                                       \
    type* init##type(void) {                                                                       \
        type* array = malloc(sizeof(type));                                                        \
        nullCheck(array);                                                                          \
        array->cap = size;                                                                         \
        array->len = 0;                                                                            \
        array->val = malloc(sizeof(malloc_type) * array->cap);                                     \
        nullCheck(array->val);                                                                     \
        return array;                                                                              \
    }

#define ENSURE_SIZE(type, realloc_type)                                                            \
    void ensureSize##type(type* array) {                                                           \
        if (array->len + 1 >= array->cap) {                                                        \
            array->cap *= 2;                                                                       \
            array->val = realloc(array->val, sizeof(realloc_type) * array->cap);                   \
            nullCheck(array->val);                                                                 \
        }                                                                                          \
    }

#define FREE(type, free_type)                                                                      \
    void free##type(type* array) {                                                                 \
        for (size_t i = 0; i < array->len; i++) {                                                  \
            free##free_type(array->val[i]);                                                        \
        }                                                                                          \
        free(array->val);                                                                          \
        free(array);                                                                               \
    }

#define APPEND(type, append_type)                                                                  \
    void append##type(type* array, append_type toAppend) {                                         \
        ensureSize##type(array);                                                                   \
        array->val[array->len++] = toAppend;                                                       \
    }

void nullCheck(void* ptr) {
    if (ptr == NULL) {
        printf("something went pretty wrong :)\n");
        exit(1);
    }
}

void freechar(char ch) {
    return;
}

DYN_STRUCT(char*, String);
DYN_STRUCT(String**, Array);
INIT_STRUCT(Array, String*, ARRAY_SIZE)
INIT_STRUCT(String, char, STRING_SIZE)
ENSURE_SIZE(Array, String*)
ENSURE_SIZE(String, char)
APPEND(Array, String*)
APPEND(String, char)
FREE(String, char)
FREE(Array, String)

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
    WHITESPACE,
    NEW_LINE,
    DIVIDER,
    NUMBER,
    MATH,
} Type;

int isAlpha(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

int isWord(char ch) {
    return isAlpha(ch) || isDigit(ch);
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
    while (left < right) {
        if (!isAlpha(string->val[left]))
            return 0;
        if (!isAlpha(string->val[right]))
            return 0;
        if (string->val[left] != string->val[right]) {
            return 0;
        }
        left++;
        right--;
    }
    if (!isAlpha(string->val[left]))
        return 0;
    return 1;
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
    if (len > cap)
        cap *= 2;
    str1->cap = cap;
    str1->val = realloc(str1->val, sizeof(char) * str1->cap);
    for (size_t i = str1->len; i < len; i++) {
        str1->val[i] = str2->val[i - str1->len];
    }
    str1->len = len;
    return str1;
}

void delete (Array* array, size_t index) {
    if (index >= array->len)
        return;
    freeString(array->val[index]);
    for (size_t i = index; i < array->len; i++) {
        array->val[i] = array->val[i + 1];
    }
    array->len--;
}

void getArray(Array* array, Files* files) {
    unsigned char word = 0;
    char ch = (char) fgetc(files->input);
    while (!feof(files->input)) {
        if (word) {
            if (isWord(ch)) {
                appendString(array->val[array->len - 1], ch);
            } else {
                word = 0;
                String* str = initString();
                appendString(str, ch);
                appendArray(array, str);
            }
        } else {
            String* str = initString();
            appendString(str, ch);
            appendArray(array, str);
            if (isWord(ch)) {
                word = 1;
            }
        }
        ch = (char) fgetc(files->input);
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
    free(string->val);
    string->len = 0;
    string->cap = STRING_SIZE;
    string->val = malloc(sizeof(char) * string->cap);
    nullCheck(string->val);
    return string;
}

String* toString(String* string, int number) {
    size_t size = nLen(number);
    string = clearString(string);
    for (size_t i = 0; i < size; i++) {
        int cur_num = (number / ((times(10, size - i - 1) / 10)) % 10);
        appendString(string, (char) (cur_num + '0'));
    }
    return string;
}

void pushBackString(String* string, const char* str) {
    size_t size = strlen(str);
    for (size_t i = 0; i < size; i++) {
        appendString(string, str[i]);
    }
}

String* stringWithString(String* string, const char* str) {
    string = clearString(string);
    pushBackString(string, str);
    return string;
}

int toNumber(String* string) {
    if (string->len > 9)
        return -1;
    int sum = 0;
    for (size_t i = 0; i < string->len; i++) {
        sum += ((int) (string->val[i] - '0')) * (times(10, (string->len - i - 1)) / 10);
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
    char fLetter = string->val[0];
    if (isWord(fLetter)) {
        for (size_t i = 0; i < string->len; i++) {
            if (!isDigit(string->val[i]))
                number = 0;
        }
        if (number)
            return NUMBER;
        return WORD;
    }
    if (isMath(fLetter))
        return MATH;
    if (isNewLine(fLetter))
        return NEW_LINE;
    if (isWhiteSpace(fLetter))
        return WHITESPACE;
    return DIVIDER;
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

void initState(State* state) {
    zeroState(state);
    state->change = 0;
    state->word = 0;
    state->parentheses = 0;
    state->parenCheck = 0;
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
                        delete (array, i--);
                        state.newlines++;
                        state.change = 1;
                        break;
                    }
                    if (state.newlines > 1) {
                        delete (array, i--);
                        state.change = 1;
                        state.newlines++;
                        break;
                    }
                    state.newlines++;
                    state.glueCheck = 0;
                    break;
                case WHITESPACE:
                    if (i == 0 || i == array->len - 1) {
                        delete (array, i--);
                        state.change = 1;
                        state.spaces++;
                        break;
                    }
                    if (state.spaces > 0 || state.newlines > 0) {
                        delete (array, i--);
                        state.change = 1;
                        state.spaces++;
                        break;
                    }
                    state.spaces++;
                    state.glueCheck = 0;
                    break;
                case DIVIDER:
                    if (array->val[i]->val[0] == '(') {
                        state.parentheses = i;
                        state.parenCheck = 1;
                    }
                    int check = state.parenCheck && state.word == 1;
                    if (array->val[i]->val[0] == ')' && check) {
                        delete (array, state.parentheses);
                        state.change = 1;
                        i--;
                        delete (array, i--);
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
                        stringForCheck->val[0] = '\0';
                        for (size_t j = state.glue; j <= i; j++) {
                            stringForCheck = concatenate(stringForCheck, array->val[j]);
                        }
                        if (isPalindrom(stringForCheck)) {
                            stringWithString(array->val[state.glue], "PALINDROM");
                            for (size_t j = state.glue + 1; j <= i;) {
                                delete (array, j);
                                i--;
                            }
                            state.change = 1;
                        }
                        freeString(stringForCheck);
                    }
                    if (state.parenCheck && !state.glueCheck) {
                        state.word++;
                    }
                    if (!state.glueCheck &&
                        ((state.parenCheck && state.word == 1) || !state.parenCheck)) {
                        state.glue = i;
                        state.glueCheck = 1;
                    }
                    size_t oldGlue = state.glue;
                    unsigned char oldGlueCheck = state.glueCheck;
                    zeroState(&state);
                    state.glue = oldGlue;
                    state.glueCheck = oldGlueCheck;
                    break;
                case NUMBER:
                    if (!state.numberCheck) {
                        state.number = i;
                        state.numberCheck = 1;
                        state.mathCheck = 0;
                    } else if (state.mathCheck == 1) {
                        int firstNumber = toNumber(array->val[state.number]);
                        int secondNumber = toNumber(array->val[i]);
                        char op = array->val[state.math]->val[0];
                        array->val[state.number] =
                            calculation(firstNumber, secondNumber, op, array->val[state.number]);
                        for (size_t j = state.number + 1; j <= i;) {
                            delete (array, j);
                            i--;
                        }
                        state.numberCheck = 0;
                        state.change = 1;
                    }
                    if (state.parenCheck)
                        state.word++;
                    else
                        state.word = 0;
                    size_t oldNumber = state.number;
                    unsigned char oldNumberCheck = state.numberCheck;
                    zeroState(&state);
                    state.numberCheck = oldNumberCheck;
                    state.number = oldNumber;
                    break;
                case MATH:
                    state.spaces = 0;
                    state.newlines = 0;
                    state.glueCheck = 0;
                    if (state.parenCheck) {
                        state.word++;
                    } else {
                        state.word = 0;
                    }
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

void printString(String* string, FILE* file) {
    for (size_t i = 0; i < string->len; i++) {
        fputc(string->val[i], file);
    }
}

void writeToFile(Array* array, Files* files) {
    for (size_t i = 0; i < array->len; i++) {
        printString(array->val[i], files->output);
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
    if (argc > 3) {
        printf("too much arguments supplied");
        exit(1);
    }
    Array* arr = initArray();
    Files* files = initFiles(argv);
    getArray(arr, files);
    processArray(arr);
    writeToFile(arr, files);
    freeArray(arr);
    freeFiles(files);
}
