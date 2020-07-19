#ifndef _INCLUDE_COMMON_H
#define _INCLUDE_COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define NOT_REACHED()\
   do {\
      fprintf(stderr, "NOT_REACHED: %s:%d In function %s()\n", \
	 __FILE__, __LINE__, __func__);\
      while (1);\
   } while (0);

#endif
