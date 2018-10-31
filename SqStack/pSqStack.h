#ifndef _PSQSTACK_H_
#define _PSQSTACK_H_

#ifndef _INC_STDLIB
#include <stdlib.h>
#ifndef _INC_STDLIB
#define _INC_STDLIB
#endif
#endif
//malloc(), realloc(), free()

#define STACK_INIT_SIZE	128
#define STACKINCREMENT	64

typedef unsigned long long SElemType;

typedef struct{
	SElemType* base;
	SElemType* top;
	int stacksize;
}SqStack;

int InitStack(SqStack* S, int size)
{
	S->base=(SElemType*)malloc(size*sizeof(SElemType)+1);
	if(!S->base)
		return -1;
	S->top=S->base;
	S->stacksize=size;
	return 0;
}

int rInitStack(SqStack* S, int size)
{
	SElemType* p;
	int len=S->top-S->base;
	p=(SElemType*)realloc(S->base, size*sizeof(SElemType)+1);
	if(!p)
		return -1;
	S->base=p;
	S->top=S->base+len;
	S->stacksize=size;
	return 0;
}

void DestroyStack(SqStack* S)
{
	free(S->base);
	S->stacksize=0;
}

void ClearStack(SqStack* S)
{
	S->top=S->base;
}

int StackLength(SqStack* S)
{
	return S->top-S->base;
}

int GetTop(SqStack* S, SElemType* e)
{
	if(S->top==S->base)
		return -1;
	*e=*S->top;
	return 0;
}

int Push(SqStack* S, SElemType e)
{
	SElemType* p;
	int len=S->top-S->base;
	if( len==S->stacksize ){
		p=(SElemType*)realloc(S->base, sizeof(SElemType)*(S->stacksize+STACKINCREMENT+1));
		if(!p)
			return -1;
		S->base=p;
		S->top=S->base+len;
		S->stacksize+=(STACKINCREMENT+1);
	}
	*(++S->top)=*(SElemType*)&e;
}

int Pop(SqStack* S, SElemType* e)
{
	if(S->top==S->base)
		return -1;
	if(e)
		*e=*S->top;
	S->top--;
	return 0;
}

int StackTraverse(SqStack* S, int visit(SElemType*))
{
	int ret=0;
	SElemType* p=S->base;
	do{
		if(p++>=S->top)
			break;
		ret=visit(p);
	}while(!ret);
	return ret;
}

int PrintStack(SqStack* S)
{
	SElemType* p=S->base;
	printf("base-> [ ] ");
	while(p!=S->top)
		printf("%lld ", *++p);
	printf("<-top\n");
}

int PrintStackX(SqStack* S)
{
	SElemType* p=S->top;
	printf("---->>>TOP<<<<----\n");
	while(p!=S->base)
		printf("0x%016llX\n", *p--);
	printf("---->>>BASE<<<----\n");
}












#endif