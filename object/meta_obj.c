#include "obj_fn.h"
//新建模块
ObjModule* newObjModule( const char* modName) {
   ObjModule* objModule = ALLOCATE( ObjModule);
   if (objModule == NULL) {
      MEM_ERROR("allocate ObjModule failed!"); 
   }

   //ObjModule是元信息对象,不属于任何一个类
   initObjHeader(&objModule->objHeader, OT_MODULE);

   StringBufferInit(&objModule->moduleVarName);
   ValueBufferInit(&objModule->moduleVarValue);

   objModule->name = NULL;   //核心模块名为NULL
   if (modName != NULL) {
      objModule->name = newObjString(modName, strlen(modName));
   }

   return objModule;
}


