#include "lalloc.h"

int initMemoryPool(MemoryPool* arena, int total_size) {
  arena->data = malloc(total_size);
  if (arena->data == NULL) {
    return -1;
  }
  arena->size     = total_size;
  arena->position = 0;
  return 0;
}

int freeMemoryPool(MemoryPool* arena) {
  if (arena->data == NULL) {
    return -1;
  }
  free(arena->data);
  arena->data     = NULL;
  arena->size     = 0;
  arena->position = 0;
  return 0;
}

int resetMemoryPool(MemoryPool* arena) {
  if (arena->data == NULL) {
    return -1;
  }
  arena->position = 0;
  return 0;
}

void* mpalloc(MemoryPool* arena, int size) {
  if (arena->position + size > arena->size) {
    return NULL;
  }
  void* slice = &(arena->data[arena->position]);
  arena->position += size;

  return slice;
}
