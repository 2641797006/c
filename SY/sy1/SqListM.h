#ifndef _SQLISTM_H_
#define _SQLISTM_H_

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif

#ifndef _INC_MEMORY
#include <memory.h>
#endif

#ifndef _PTYPE_H_
#include <__pink/ptype.h>
#endif

#define _ret_ __PRET__

#ifndef ElemType
#define ElemType QWORD
#endif

typedef int (*VISIT)(ElemType*);

QWORD LIST_INIT_SIZE=128;
QWORD LISTINCREMENT=64;

typedef struct{
	ElemType* elem;
	QWORD length;
	QWORD listsize;
}SqList;

#define CopyElem(dest, src) memcpy(dest, src, sizeof(*(src)))

int InitList(SqList* L)
{
	L->elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L->elem)
		return -1;
	L->length=0;
	L->listsize=LIST_INIT_SIZE;
	return 0;
}

void DestroyList(SqList* L)
{
	free(L->elem);
	L->length=0;
	L->listsize=0;
}

int ListTraverse(SqList* L, VISIT visit)
{
	ElemType* pe=L->elem;
	int i, len=L->length, ret;
	for(i=1;i<=len;i++,pe++){
		ret=visit(pe);
		if(ret){
			_ret_=i;
			return ret;
		}
	}
	return 0;
}

int ListInsert(SqList* L, int i, ElemType* pe)
{
	ElemType *pe0, *pe1;
	if(i<1 || i>L->length+1)
		return -1;
	pe0=L->elem;
	if(L->length==L->listsize){
		pe0=(ElemType*)realloc(pe0, (L->listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!pe0)
			return -2;
		L->elem=pe0;
		L->listsize+=LISTINCREMENT;
	}
	pe1=pe0+i-1;
	pe0+=L->length;
	while(pe0>pe1)
		CopyElem(pe0, --pe0);
	CopyElem(pe1, pe);
	L->length++;
	return 0;
}

int ListDelete(SqList* L, int i, ElemType* pe)
{
	ElemType *pe0, *pe1;
	if(i<1 || i>L->length)
		return -1;
	pe0=L->elem+i-1;
	pe1=L->elem+L->length-1;
	pe&&CopyElem(pe, pe0);
	do
		CopyElem(pe0, pe0+1);
	while(++pe0<pe1);
	L->length--;
	return 0;
}

typedef void (*PrintElem)(ElemType*);

void PrintList(SqList* L, PrintElem printelem)
{
	ElemType *pe=L->elem, *pe1=pe+L->length-1;
	while(pe<=pe1)
		printelem(pe++);
	printf("\n");
}

typedef int (*FileIoElem)(FILE*, ElemType*);

int fprintList(SqList* L, const char* filename, const char* openmode, FileIoElem fprintElem)
{
	FILE* fp;
	ElemType* pe;
	int i, len, ret;
	fp=fopen(filename, openmode);
	if(!fp)
		return ferror(fp);
	pe=L->elem;
	len=L->length;
	for(i=0;i<len;i++,pe++){
		ret=fprintElem(fp, pe);
		if(ret)
			return ret;
	}
	if(fclose(fp))
		return ferror(fp);
	return -520;
}

























#endif