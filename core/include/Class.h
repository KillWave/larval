#ifndef __CLASS_H__
#define __CLASS_H__
#include "autofree.h"
#define fn(return_type, function_name,function_args, function_body)  autofree return_type(*function_name)function_args;  function_name = lamda(return_type,function_args,function_body)
#define lamda(return_type,function_args, function_body) ({return_type func_name function_args function_body func_name;})
#define class void
#define implements(type) (type*this)
#define new(type,func) ({type* t; func(t); t;})

#endif