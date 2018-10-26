#ifndef _PSQSTACKX_H_
#define _PSQSTACKX_H_

#ifndef _INC_STDLIB
#include <stdlib.h>
#ifndef _INC_STDLIB
#define _INC_STDLIB
#endif
#endif
//malloc(), realloc(), free()

#ifndef _INC_STRING
#include <string.h>
#ifndef _INC_STRING
#define _INC_STRING
#endif
#endif

typedef unsigned long long QWORD;

#define STACK_INIT_SIZE	128
#define STACKINCREMENT	64

struct{
	QWORD* base;
	QWORD* top;
	int stacksize;
}__P_SqStack_struct__={0};
#define S (&__P_SqStack_struct__)

QWORD push_err=0;
QWORD pop_err=0;

QWORD InitStack()
{
	S->base=(QWORD*)malloc(STACK_INIT_SIZE*sizeof(QWORD));
	if(!S->base)
		return -1;
	S->top=S->base;
	S->stacksize=STACK_INIT_SIZE-1;
	return 0;
}

QWORD ExpandStack(QWORD n)
{
	*S->base=S->top-S->base;
	if(*S->base+n<=S->stacksize)
		return 0;
	QWORD* p=(QWORD*)realloc(S->base, S->stacksize+STACKINCREMENT+1);
	if(!p){
		push_err=-1;
		return -1;
	}
	S->base=p;
	S->top=S->base+*S->base;
	S->stacksize+=STACKINCREMENT;
	return 0;
}

#define push(value){\
	QWORD n=(sizeof(value)+sizeof(QWORD)-1)/sizeof(QWORD);\
	if(!ExpandStack(n)){\
		inline void Pmemcpy(void* _, ...)\
		{\
			_ = sizeof(value)>sizeof(QWORD) ? (void*)*(&_+1) : &_+1;\
			memcpy(__P_SqStack_struct__.top+1, _, sizeof(value));\
		}\
		Pmemcpy(NULL, value);\
		__P_SqStack_struct__.top+=n;\
	}\
}

#define pop(address){\
	QWORD n=(sizeof(*address)+sizeof(QWORD)-1)/sizeof(QWORD);\
	if(__P_SqStack_struct__.top-__P_SqStack_struct__.base>=n){\
		memcpy(address, __P_SqStack_struct__.top-n+1, sizeof(*address));\
		__P_SqStack_struct__.top-=n;\
	}\
	else\
		pop_err=-1;\
}

#define Push(x) push(x)
#define Pop(x) pop(x)

#undef S
#endif