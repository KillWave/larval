#ifndef _OBJECT_LIST_H
#define _OBJECT_LIST_H
#include "class.h"
typedef struct
{
    ObjHeader objHeader;
    ValueBuffer elements; //list中的元素
} ObjList;                //list对象

ObjList *newObjList(uint32_t elementNum);
Value removeElement(ObjList *objList, uint32_t index);
void insertElement(ObjList *objList, uint32_t index, Value value);
#endif