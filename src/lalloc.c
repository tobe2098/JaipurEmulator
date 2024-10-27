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
  void*   slice   = &(arena->data[arena->position]);
  size_mt new_ptr = ((size_mt)slice + sizeof(void*) - 1) & ~(sizeof(void*) - 1);
  if (new_ptr + size > arena->size) {
    return NULL;
  }
  arena->position = size + (new_ptr - (size_mt)slice);

  return (void*)new_ptr;
}
