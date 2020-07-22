#include "obj_range.h"


//æ–°å»ºrangeå¯¹è±¡
ObjRange* newObjRange(int from, int to) {
   ObjRange* objRange = ALLOCATE(ObjRange);
   initObjHeader(&objRange->objHeader, OT_RANGE);
   objRange->from = from;
   objRange->to = to;
   return objRange;
}
