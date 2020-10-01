/*
** == Exceptions ==
**
**  Exceptions in libCello follow fairly normal
**  semantics with one main difference.
**
**  Any object can be thrown and caught.
**
*/
#ifndef __Exception_H
#define __Exception_H
#include <setjmp.h>
#include <signal.h>
#include <string.h>
#include "./prelude.h"
#define try \
  Exception_Register_Signals(); \
	jmp_buf __jmp_buf; \
	int __jmp_result = setjmp(__jmp_buf); \
	if (!__jmp_result) jmp_stack_push(&__jmp_buf); \
  if (!__jmp_result)

#define catch(e) \
	int e = __jmp_result; \
	if (!e) jmp_stack_pop(); \
	else

#define throw(msg_) global Exception Error; if(msg_ == NULL){  fprintf(stderr,"error:%s line:%d file:%s date:%s\n",Error.msg,__LINE__,__FILE__,__DATE__);  } else{fprintf(stderr,"error:%s line:%d file:%s date:%s\n",msg_,__LINE__,__FILE__,__DATE__);free(Error.msg); }   
#define MAX_JUMP 1024
typedef jmp_buf* jmp_stack[MAX_JUMP];
jmp_stack g_js;
int g_jsidx;

void jmp_stack_push(jmp_buf* jb)
{
	g_js[g_jsidx++] = jb;
}

jmp_buf* jmp_stack_pop()
{
	return g_js[--g_jsidx];
}

interface
{
  int signalCode;
  char msg[];
}Exception;

Exception Error;


void Exception_Signal(int sig) {
 
  switch(sig) {
    case SIGABRT:
        Error.signalCode = sig;
        strcpy( Error.msg,"Program Aborted");
      break;
    case SIGFPE:  
        Error.signalCode = sig;
        strcpy(Error.msg,"Division by Zero");   
     break;
    case SIGILL: 
        Error.signalCode = sig;
        strcpy(Error.msg,"Illegal Instruction");
     break;
    case SIGINT:  
        Error.signalCode = sig;
        strcpy(Error.msg, "Program Interrupted");
     break;
    case SIGSEGV: 
        Error.signalCode = sig;
        strcpy(Error.msg, "Segmentation fault");
     break;
    case SIGTERM: 
        Error.signalCode = sig;
        strcpy(Error.msg, "Program Terminated");
     break;
  }
  longjmp(*jmp_stack_pop(), sig);
}
void Exception_Register_Signals(){
    signal(SIGABRT, Exception_Signal);
    signal(SIGFPE,  Exception_Signal);
    signal(SIGILL,  Exception_Signal);
    signal(SIGINT,  Exception_Signal);
    signal(SIGSEGV, Exception_Signal);
    signal(SIGTERM, Exception_Signal);
}



#endif
