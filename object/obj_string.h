#ifndef _OBJECT_STRING_H
#define _OBJECT_STRING_H
#include <string.h>
#include "header_obj.h"

typedef struct {
   ObjHeader objHeader;
   uint32_t hashCode;  //字符串的哈希值
   CharValue value;
} ObjString;

uint32_t hashString(char* str, uint32_t length);
void hashObjString(ObjString* objString);
ObjString* newObjString(const char* str, uint32_t length);
#endif
