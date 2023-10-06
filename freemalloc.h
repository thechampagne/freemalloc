#ifndef __FREEMALLOC__
#define __FREEMALLOC__

#include <stdlib.h>

#ifndef FREEMALLOC_ADDR_CAPACITY
#define FREEMALLOC_ADDR_CAPACITY 124
#endif

#ifndef FREEMALLOC_MALLOC
#define FREEMALLOC_MALLOC(size) malloc(size)
#endif

#ifndef FREEMALLOC_CALLOC
#define FREEMALLOC_CALLOC(num, size) calloc(num, size)
#endif

#ifndef FREEMALLOC_REALLOC
#define FREEMALLOC_REALLOC(ptr, new_size) realloc(ptr, new_size)
#endif

#ifndef FREEMALLOC_FREE
#define FREEMALLOC_FREE(ptr) free(ptr)
#endif

typedef struct {
  void* addr[FREEMALLOC_ADDR_CAPACITY];
  size_t addr_len;
} freemalloc_t;

inline void* freemalloc_malloc(freemalloc_t* freemalloc, size_t size)
{
  void* ptr = FREEMALLOC_MALLOC(size);
  if (ptr == NULL) return NULL;
  freemalloc->addr[freemalloc->addr_len] = ptr;
  freemalloc->addr_len++;
  return ptr;
}

inline void* freemalloc_calloc(freemalloc_t* freemalloc, size_t num, size_t size);
{
  void* ptr = FREEMALLOC_CALLOC(num, size);
  if (ptr == NULL) return NULL;
  freemalloc->addr[freemalloc->addr_len] = ptr;
  freemalloc->addr_len++;
  return ptr;
}

void* freemalloc_realloc(freemalloc_t* freemalloc, void* ptr, size_t new_size)
{
  void* new_ptr = FREEMALLOC_REALLOC(ptr, size);
  if (new_ptr == NULL) return NULL;
  for (size_t i = 0; i < freemalloc->addr_len; i++)
    {
      if (freemalloc->addr[i] == ptr) freemalloc->addr[i] = new_ptr;
    }
  return new_ptr;
}

void freemalloc_free(freemalloc_t* freemalloc, void* ptr)
{
  for (size_t i = 0; i < freemalloc->addr_len; i++)
    {
      if (freemalloc->addr[i] == ptr)
	{
	  FREEMALLOC_FREE(freemalloc->addr[i]);
	  freemalloc->addr[i] = NULL;
	}
    }
}

void freemalloc_free_all(freemalloc_t* freemalloc)
{
  for (size_t i = 0; i < freemalloc->addr_len; i++)
    {
      FREEMALLOC_FREE(freemalloc->addr[i]);
      freemalloc->addr[i] = NULL;
    }
}

#endif // __FREEMALLOC__
