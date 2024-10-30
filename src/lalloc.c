#include "lalloc.h"
// Get system page size
static size_t _getPageSize(void) {
#ifdef _WIN32
  SYSTEM_INFO si;
  GetSystemInfo(&si);
  return si.dwPageSize;
#else
  return sysconf(_SC_PAGESIZE);
#endif
}

static inline size_t align_up(size_t n, size_t align) {
  return (n + align - 1) & ~(align - 1);
}

int initPagePool(PagePool* arena, int total_size) {
  // Assuming the total_size already accounts for the size considering that pages cannot be filled
  arena->page_collection = (MemoryPage*)calloc(total_size / _getPageSize(), sizeof(MemoryPage));
  if (arena->page_collection == NULL) {
    return -1;
  }
  arena->total_pages = total_size / _getPageSize();
  (void)initMemoryPage(&arena->page_collection[0]);
  return 0;
}

static MemoryPage* initMemoryPage(MemoryPage* mempage) {
  mempage->data = _aligned_malloc(_getPageSize(), _getPageSize());
  if (mempage->data == NULL) {
    return NULL;
  }
  mempage->size = _getPageSize();
  return mempage;
}

int freeMemoryPool(PagePool* arena) {
  if (arena->page_collection == NULL) {
    return -1;
  }
  MemoryPage* ptr = arena->page_collection;
  while (ptr) {
    _aligned_free(ptr->data);
    ptr->next;
  }
  free(arena->page_collection);
  arena->page_collection = NULL;
  arena->total_pages     = 0;
  return 0;
}

int resetMemoryPool(PagePool* arena) {
  if (arena->page_collection == NULL) {
    return -1;
  }
  MemoryPage* ptr = arena->page_collection;
  while (ptr) {
    ptr->position = 0;
    ptr->next;
  }
  arena->current_page = 0;
  return 0;
}

void* mpalloc(PagePool* arena, int size) {
  if (arena->page_collection[arena->current_page].position) {
    void* slice = &(arena->data[arena->position]);
  }
  size_mt new_ptr = ((size_mt)slice + sizeof(void*) - 1) & ~(sizeof(void*) - 1);
  if (new_ptr + size > arena->size) {
    return NULL;
  }
  arena->position = size + (new_ptr - (size_mt)slice);

  return (void*)new_ptr;
}

/*#define CACHE_LINE_SIZE 64
#define PAGE_SIZE 4096

typedef struct PagePool {
    uint8_t* data;
    size_t   size;
    size_t   position;
} PagePool;

static inline size_t align_up(size_t n, size_t align) {
    return (n + align - 1) & ~(align - 1);
}

void* mpalloc(PagePool* arena, size_t size) {
    size_t aligned_size = align_up(size, CACHE_LINE_SIZE);
    size_t current_pos = arena->position;

    // Check if allocation would cross page boundary
    size_t page_offset = current_pos & (PAGE_SIZE - 1);
    if (page_offset + aligned_size > PAGE_SIZE) {
        // Align up to next page boundary
        current_pos = align_up(current_pos, PAGE_SIZE);
    }

    // Verify we have enough space
    if (current_pos + aligned_size > arena->size) {
        return NULL;
    }

    void* ptr = &arena->data[current_pos];
    arena->position = current_pos + aligned_size;
    return ptr;
}

int initMemoryPool(PagePool* arena, size_t total_size) {
    // Calculate how many complete pages we need
    size_t struct_size = align_up(sizeof(struct ThreadData), CACHE_LINE_SIZE);
    size_t structs_per_page = PAGE_SIZE / struct_size;
    size_t num_pages = (total_size + PAGE_SIZE - 1) / PAGE_SIZE;

    // Allocate aligned to page size
    if (posix_memalign((void**)&arena->data, PAGE_SIZE, num_pages * PAGE_SIZE) != 0) {
        return -1;
    }

    // Pre-touch pages to prevent faults during thread execution
    for (size_t i = 0; i < num_pages; i++) {
        arena->data[i * PAGE_SIZE] = 0;
    }

    arena->size = num_pages * PAGE_SIZE;
    arena->position = 0;
    return 0;
}

// Usage demonstration
void demonstrate_allocation() {
    PagePool arena;
    size_t num_threads = 100;  // Example

    // Calculate required size including potential page padding
    size_t struct_size = align_up(sizeof(struct ThreadData), CACHE_LINE_SIZE);
    size_t structs_per_page = PAGE_SIZE / struct_size;
    size_t num_pages = (num_threads + structs_per_page - 1) / structs_per_page;
    size_t total_size = num_pages * PAGE_SIZE;

    if (initMemoryPool(&arena, total_size) != 0) {
        return;
    }

    // Allocate thread structs
    struct ThreadData* thread_data[num_threads];
    for (size_t i = 0; i < num_threads; i++) {
        thread_data[i] = mpalloc(&arena, sizeof(struct ThreadData));

        // Debug check
        uintptr_t addr = (uintptr_t)thread_data[i];
        assert((addr & (CACHE_LINE_SIZE - 1)) == 0);  // Cache line aligned
        assert(((addr & (PAGE_SIZE - 1)) + struct_size) <= PAGE_SIZE);  // Doesn't cross page
    }
}*/