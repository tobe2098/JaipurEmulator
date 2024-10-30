#ifndef _LINEAR_ALLOCATOR_ARENA_HEADER
#define _LINEAR_ALLOCATOR_ARENA_HEADER

#define NULL     0
#define BIT_WORD sizeof(void*)
#include "game_constants.h"

#include <stddef.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#include <unistd.h>
#endif

typedef struct {
    void*       data;
    size_mt     position;
    size_mt     size;
    MemoryPage* next;
} MemoryPage;

typedef struct {
    MemoryPage* page_collection;
    size_mt     current_page;
    size_mt     total_pages;
} PagePool;

int initPagePool(PagePool* arena, int total_size);
int freeMemoryPool(PagePool* arena);
int resetMemoryPool(PagePool* arena);

void* mpalloc(PagePool* arena, int size);

/*
Fix the arena so that it uses a page every time, and then after 7 it uses a new page
Jaipur cache line invalidation, duplicate cannot be allocating, when you allocate in bulk you will get an arena, then just free it
*/

#endif