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

QWORD InitStack()
{
	S->base=(QWORD*)malloc(STACK_INIT_SIZE*sizeof(QWORD));
	if(!S->base)
		return -1;
	S->top=S->base;
	S->stacksize=STACK_INIT_SIZE-1;
	return 0;
}

void DestroyStack()
{
	free(S->base);
}

QWORD Ppush(QWORD _, ...)
{
	void* p;
	QWORD size=(_+sizeof(QWORD)-1)/sizeof(QWORD);
	*S->base=S->top-S->base;
	if(*S->base+size>S->stacksize){
		p=(void*)realloc(S->base, sizeof(QWORD)*(S->stacksize+1+STACKINCREMENT+size));
		if(!p)
			return -1;
		S->base=(QWORD*)p;
		S->top=S->base+*S->base;
		S->stacksize+=(STACKINCREMENT+size);		
	}
	p = _>sizeof(QWORD) ? (void*)*(&_+1) : (void*)(&_+1);
	memcpy(S->top+1, p, _);
	S->top+=size;
	return 0;
}

QWORD Ppop(QWORD _, void* address)
{
	QWORD size=(_+sizeof(QWORD)-1)/sizeof(QWORD);
	if(S->top-S->base<size)
		return -1;
	memcpy(address, S->top-size+1, _);
	S->top-=size;
	return 0;
}

#define push(value) Ppush(sizeof(value), value)
#define pop(address) Ppop(sizeof(*address), address)

#define Push(x) push(x)
#define Pop(x) pop(x)

#undef S
#endif