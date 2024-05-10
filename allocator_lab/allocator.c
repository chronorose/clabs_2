#include "allocator.h"
#include <string.h>

static size_t allocatorSize;
static char* allocator[ARENA_COUNT];

typedef struct _list {
    struct _list* next;
} List;

typedef struct {
    List* freeList;
    char* current;
} Header;

unsigned char getRandomNumber(unsigned char lower, unsigned char upper) {
    return (unsigned char) (rand() % (upper - lower + 1)) + lower;
}

size_t getArenaNumber(size_t size) {
    size_t arenaNumber = (size - 1) / 8;
    if (arenaNumber > allocatorSize)
        arenaNumber = allocatorSize;
    return arenaNumber;
}

size_t getArenaSize(size_t size) {
    size_t arenaSize = (size + 1) * 8;
    if (size > allocatorSize)
        arenaSize = KB * 16;
    return arenaSize;
}

void preparation(size_t iter) {
    allocator[iter] = *allocator + (iter * ARENA_SIZE);
    List* list = (List*) (void*) allocator[iter];
    void* cap;
    size_t step;
    if (iter == allocatorSize) {
        step = KB * 2;
        cap = *allocator + (HEAP_SIZE - KB * 16);
    } else {
        step = iter + 1;
        cap = *allocator + ((iter + 1) * ARENA_SIZE);
    }
    while ((void*) (list + step) < cap) {
        list->next = list + step;
        list = list->next;
    }
    list->next = NULL;
}

void initAllocator() {
    srand((unsigned int) time(NULL));
    allocatorSize = getRandomNumber(8, 32) - 1;
    allocator[0] = malloc(sizeof(char) * HEAP_SIZE);
    nullCheck(allocator[0]);
    for (size_t i = 0; i < allocatorSize; i++) {
        preparation(i);
    }
    preparation(allocatorSize);
}

void* myCalloc(size_t number, size_t size) {
    void* arr = myMalloc(number * size);
    if (arr == NULL)
        return NULL;
    memset(arr, 0, number * size);
    return arr;
}

void* myMalloc(size_t size) {
    if (size == 0)
        return NULL;
    size_t offset = getArenaNumber(size);
    List* list = (List*) (void*) allocator[offset];
    List* ret = list->next;
    if (ret == NULL)
        return NULL;
    List* newNext = list->next->next;
    ret->next = NULL;
    list->next = newNext;
    return (void*) ret;
}

size_t getArenaByPointer(void* ptr) {
    return (size_t) ((char*) ptr - *allocator) / ARENA_SIZE;
}

void myFree(void* ptr) {
    if (ptr == NULL)
        return;
    size_t diff = getArenaByPointer(ptr);
    if (diff > allocatorSize)
        return;
    List* list = (List*) (void*) allocator[diff];
    List* newList = (List*) ptr;
    newList->next = list->next;
    list->next = newList;
}

void* myRealloc(void* ptr, size_t size) {
    if (ptr == NULL && size != 0)
        return myMalloc(size);
    if (ptr == NULL && size == 0)
        return NULL;
    size_t diff = getArenaByPointer(ptr);
    size_t offset = getArenaNumber(size);
    if (diff > allocatorSize)
        return NULL;
    if (diff == offset)
        return ptr;
    size_t newSize = getArenaSize(getArenaNumber(size));
    void* new = myMalloc(newSize);
    if (new == NULL)
        return NULL;
    new = memcpy(new, ptr, newSize);
    myFree(ptr);
    return new;
}

void destroyAllocator() {
    free(allocator[0]);
}
