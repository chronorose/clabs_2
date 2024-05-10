#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ARENA_SIZE (1 << 20)
#define HEAP_SIZE (ARENA_SIZE * 50)
#define KB (1 << 10)
#define ARENA_COUNT 33

void nullCheck(void* ptr);

void initAllocator(void);

void* myMalloc(size_t size);

void myFree(void* ptr);

void* myRealloc(void* ptr, size_t size);

void destroyAllocator(void);

#endif
