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

int InitStack()
{
	S->base=(QWORD*)malloc( (DWORD)( STACK_INIT_SIZE*sizeof(QWORD) ) );
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

int StackEmpty()
{
	if(S->top==S->base)
		return 1;
	return 0;
}

int StackLength()
{
	return S->top-S->base;
}

int __P_GetTop(QWORD _, void* address)
{
	QWORD size=(_+sizeof(QWORD)-1)/sizeof(QWORD);
	if(S->top-S->base<size)
		return -1;
	memcpy(address, S->top-size+1, (DWORD)_);
	return 0;
}

#define GetTop(address) __P_GetTop(sizeof(*(address)), (void*)(address))

QWORD* GetTopP()
{
	return S->top;
}

void SetTopP(void* p)
{
	S->top=p;
}

int EnoughStack(QWORD _)
{
	void* p;
	QWORD size=(_+sizeof(QWORD)-1)/sizeof(QWORD);
	*S->base=S->top-S->base;
	if(*S->base+size>S->stacksize){
		p=(void*)realloc(S->base, (DWORD)( sizeof(QWORD)*(S->stacksize+1+STACKINCREMENT+size) ) );
		if(!p)
			return -1;
		S->base=(QWORD*)p;
		S->top=S->base+*S->base;
		S->stacksize+=(STACKINCREMENT+size);
		return 1;
	}
	return 0;
}

#define push(value)( \
		EnoughStack(sizeof(value))>=0 ? \
		( \
			*++__P_SqStack_struct__.top=0, \
			memcpy(__P_SqStack_struct__.top, &value, (int)sizeof(value)), \
			__P_SqStack_struct__.top+=( (sizeof(value)+sizeof(QWORD)-1)/sizeof(QWORD)-1 ), \
			(sizeof(value)+sizeof(QWORD)-1)/sizeof(QWORD) \
		) \
		: -1 )

int __P_pop(QWORD _, void* address)
{
	QWORD size=(_+sizeof(QWORD)-1)/sizeof(QWORD);
	if(S->top-S->base<size)
		return -1;
	memcpy(address, S->top-size+1, (DWORD)_);
	S->top-=size;
	return 0;
}

#define pop(address) __P_pop(sizeof(*(address)), (void*)(address))

void PrintStack()
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