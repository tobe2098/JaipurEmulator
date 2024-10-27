#ifndef _LINEAR_ALLOCATOR_ARENA_HEADER
#define _LINEAR_ALLOCATOR_ARENA_HEADER
#define NULL 0
#include <stddef.h>
#include "game_constants.h"
typedef struct {
    void*   data;
    size_mt position;
    size_mt size;
} MemoryPool;

int initMemoryPool(MemoryPool* arena, int total_size);
int freeMemoryPool(MemoryPool* arena);
int resetMemoryPool(MemoryPool* arena);

void* mpalloc(MemoryPool* arena, int size);

#endif