# freemalloc

[![](https://img.shields.io/github/license/thechampagne/freemalloc)](https://github.com/thechampagne/freemalloc/blob/main/LICENSE)

freemalloc saves all memory addresses that have been allocated using malloc or custom memory allocator to release them all using one function.

### Example
```c
/*
#define FREEMALLOC_MALLOC(size) custom_malloc(size)

#define FREEMALLOC_CALLOC(num, size) custom_calloc(num, size)

#define FREEMALLOC_REALLOC(ptr, new_size) custom_realloc(ptr, new_size)

#define FREEMALLOC_FREE(ptr) custom_free(ptr)
*/

#define FREEMALLOC_ADDR_CAPACITY 4 // number of allocations
#include "freemalloc.h"

int main(void)
{
	freemalloc_t fm;
	int* ptr1 = (int*)freemalloc_malloc(&fm, sizeof(int));
	int* ptr2 = (int*)freemalloc_malloc(&fm, sizeof(int));
	int* ptr3 = (int*)freemalloc_malloc(&fm, sizeof(int));
	int* ptr4 = (int*)freemalloc_malloc(&fm, sizeof(int));
	freemalloc_free_all(&fm);
	return 0;
}
```

### License

This repo is released under the [MIT License](https://github.com/thechampagne/freemalloc/blob/main/LICENSE).
