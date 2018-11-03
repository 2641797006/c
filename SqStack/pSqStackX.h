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

#define DWORD unsigned long

typedef unsigned long long QWORD;

#define STACK_INIT_SIZE	128
#define STACKINCREMENT	64

struct{
	QWORD* base;
	QWORD* top;
	int stacksize;
}__P_SqStack_struct__={0};
#define S (&__P_SqStack_struct__)

DWORD InitStack()
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

void ClearStack()
{
	S->top=S->base;
}

DWORD StackEmpty()
{
	if(S->top==S->base)
		return 1;
	return 0;
}

DWORD StackLength()
{
	return S->top-S->base;
}

DWORD PGetTop(QWORD _, void* address)
{
	QWORD size=(_+sizeof(QWORD)-1)/sizeof(QWORD);
	if(S->top-S->base<size)
		return -1;
	memcpy(address, S->top-size+1, (DWORD)_);
	return 0;
}

#define GetTop(address) PGetTop(sizeof(*(address)), (void*)(address))

QWORD* GetTopP()
{
	return S->top;
}

void SetTopP(void* p)
{
	S->top=p;
}

DWORD EnoughStack(QWORD space)
{
	if(!S->base)
		InitStack();
	void* p;
	*S->base=S->top-S->base;
	if(S->stacksize-*S->base<space){
		p=(void*)realloc(S->base, sizeof(QWORD)*(S->stacksize+1+STACKINCREMENT+space));
		if(!p)
			return -1;
		S->base=(QWORD*)p;
		S->top=S->base+*S->base;
		S->stacksize+=(STACKINCREMENT+space);
		return 1;
	}
	return 0;
}

DWORD Ppush(QWORD _, ...)
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

#ifdef __GNUC__
	p = _>sizeof(QWORD) ? (void*)*(&_+1) : (void*)(&_+1);
#else
	p = (void*)(&_+1);
#endif

	memcpy(S->top+1, p, (DWORD)_);
	S->top+=size;
	return 0;
}

DWORD Ppop(QWORD _, void* address)
{
	QWORD size=(_+sizeof(QWORD)-1)/sizeof(QWORD);
	if(S->top-S->base<size)
		return -1;
	memcpy(address, S->top-size+1, (DWORD)_);
	S->top-=size;
	return 0;
}

#ifdef __GNUC__
#define push(value) sizeof(value)>sizeof(QWORD) \
		? Ppush(sizeof(value), value) \
		: ( EnoughStack(1), memcpy(++__P_SqStack_struct__.top, &value, (int)sizeof(value)), 1 )
#else
#define push(value) Ppush(sizeof(value), value)
#endif

#define pop(address) Ppop(sizeof(*(address)), (void*)(address))

DWORD PrintStack()
{
	QWORD* p=S->top;
	printf("---->>>TOP<<<<----\n");
	while(p!=S->base)
		printf("0x%016llX\n", *p--);
	printf("---->>>BASE<<<----\n");
}

#undef S
#undef DWORD

#endif