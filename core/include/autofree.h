#ifndef __AUTOFREE__
#define __AUTOFREE__
#include <stdlib.h>
#include <stdarg.h>
#define autofree __attribute__((cleanup(free_stack)))
__attribute__ ((always_inline))
static inline void free_stack(void *ptr) {
    free(*(void **) ptr);
}
#define argumentsfree __attribute__((cleanup(free_arguments)))
static inline void free_arguments(void *ptr) {
    va_end(*(void **) ptr); 
}
#endif