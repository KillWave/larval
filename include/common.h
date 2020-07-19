#ifndef _INCLUDE_COMMON_H
#define _INCLUDE_COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
typedef struct vm VM;
typedef struct parser Parser;
typedef struct class Class;
// #define UNUSED __attribute__ ((unused))
#define DEBUG
#ifdef DEBUG
   #define ASSERT(condition, errMsg) \
      do {\
	 if (!(condition)) {\
	    fprintf(stderr, "ASSERT failed! %s:%d In function %s(): %s\n", \
	       __FILE__, __LINE__, __func__, errMsg); \
	    abort();\
	 }\
      } while (0);
#else
   #define ASSERT(condition, errMsg) ((void)0)
#endif

#define NOT_REACHED()\
   do {\
      fprintf(stderr, "NOT_REACHED: %s:%d In function %s()\n", \
	 __FILE__, __LINE__, __func__);\
      while (1);\
   } while (0);

#endif
