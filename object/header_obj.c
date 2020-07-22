#include "header_obj.h"

DEFINE_BUFFER_METHOD(Value)

//初始化对象头
void initObjHeader(ObjHeader* objHeader, ObjType objType) {
   objHeader->type = objType;
   objHeader->isDark = false;
}
