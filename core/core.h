#ifndef _CORE_H_
#define _CORE_H_
#include <string.h>
#include <sys/stat.h>
#include "../utils/utils.h"
#include "../object/obj_thread.h"
#define CORE_MODULE VT_TO_VALUE(VT_NULL)
extern char* rootDir;
char* readFile(const char* sourceFile);
void executeModule(Value moduleName, const char* moduleCode);
void buildCore(const char *modName);
#endif