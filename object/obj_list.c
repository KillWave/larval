#include "obj_list.h"

//新建list对象,元素个数为elementNum
ObjList* newObjList(uint32_t elementNum) {
   //存储list元素的缓冲区
   Value* elementArray = NULL;

   //先分配内存,后调用initObjHeader,避免gc无谓的遍历
   if (elementNum > 0) {
      elementArray = ALLOCATE_ARRAY( Value, elementNum);
   }
   ObjList* objList = ALLOCATE( ObjList); 

   objList->elements.datas = elementArray;
   objList->elements.capacity = objList->elements.count = elementNum;
   initObjHeader( &objList->objHeader, OT_LIST);
   return objList;
}

//在objlist中索引为index处插入value, 类似于list[index] = value
void insertElement( ObjList* objList, uint32_t index, Value value) {
   if (index > objList->elements.count - 1) {
      RUN_ERROR("index out bounded!");
   }

   //准备一个Value的空间以容纳新元素产生的空间波动
   //即最后一个元素要后移1个空间
   ValueBufferAdd( &objList->elements, VT_TO_VALUE(VT_NULL));
   
   //下面使index后面的元素整体后移一位
   uint32_t idx = objList->elements.count - 1;
   while (idx > index) {
      objList->elements.datas[idx] = objList->elements.datas[idx - 1];
      idx--;
   }

   //在index处插入数值
   objList->elements.datas[index] = value;
}

//调整list容量
static void shrinkList(  ObjList* objList, uint32_t newCapacity) {
   uint32_t newSize = newCapacity * sizeof(Value);
   memManager( objList->elements.datas, newSize);
   objList->elements.capacity = newCapacity;
}

//删除list中索引为index处的元素,即删除list[index]
Value removeElement(  ObjList* objList, uint32_t index) {
   Value valueRemoved = objList->elements.datas[index];

   //使index后面的元素前移一位,覆盖index处的元素
   uint32_t idx = index;
   while (idx < objList->elements.count) {
      objList->elements.datas[idx] = objList->elements.datas[idx + 1];
      idx++;
   }

   //若容量利用率过低就减小容量
   uint32_t _capacity = objList->elements.capacity / CAPACITY_GROW_FACTOR;
   if (_capacity > objList->elements.count) {
      shrinkList( objList, _capacity);
   }

   objList->elements.count--;
   return valueRemoved;
}
