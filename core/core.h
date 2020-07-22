#ifndef _CORE_H_
#define _CORE_H_
#include <string.h>
#include <sys/stat.h>
#include "../utils/utils.h"
extern char* rootDir;
char* readFile(const char* sourceFile);
#endif