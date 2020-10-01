#ifndef __AUTOFREE__
#define __AUTOFREE__
#include <stdlib.h>
#define autofree __attribute__((cleanup(free_stack)))
__attribute__ ((always_inline))
static inline void free_stack(void *ptr) {
    free(*(void **) ptr);
}
#endif