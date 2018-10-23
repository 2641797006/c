#ifndef _PSQLIST_H_
#define _PSQLIST_H_

#ifndef _INC_STDIO
#include <stdio.h>
#ifndef _INC_STDIO
#define _INC_STDIO
#endif
#endif

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

#ifndef _PRAND_H_
#include <__pink/prand.h>
#endif

#define LIST_INIT_SIZE	128
#define LISTINCREMENT	64

#ifndef ElemType
#define ElemType int
#endif
//ElemType is a Number

typedef struct{
	ElemType* elem;
	int length;
	int listsize;
}SqList;

typedef struct{
	ElemType* elem;
	int length;
}mSqList;

int InitList(SqList* L, int size)
{
	L->elem=(ElemType*)malloc(size*sizeof(ElemType));
	if(!L->elem)
		return -1;
	L->length=0;
	L->listsize=size;
	return 0;
}

int rInitList(SqList* L, int size)
{
	ElemType* pe;
	pe=(ElemType*)realloc(L->elem, size*sizeof(ElemType));
	if(!pe)
		return -1;
	L->elem=pe;
	if(L->length>size)
		L->length=size;
	L->listsize=size;
	return 0;
}

void DestroyList(SqList* L)
{
	free(L->elem);
	L->length=0;
	L->listsize=0;
}

ElemType* LocateElem(SqList* L, ElemType e)
{
	ElemType* pe;
	int len=L->length;
	for(pe=L->elem; *pe!=e; pe++,len--)
		if(len<2)
			return NULL;
	return pe;
}

ElemType* ListAmend(SqList* L, ElemType e, ElemType e1)
{
	ElemType* pe;
	pe=LocateElem(L, e);
	if(!pe)
		return NULL;
	*pe=e1;
	return pe;
}

int ListInsert(SqList* L, int i, ElemType e)
{
	ElemType *pe, *pe1;
	if(i<1 || i>L->length+1)
		return -1;
	pe=L->elem;
	if(L->length==L->listsize){
		pe=(ElemType*)realloc(pe, (L->listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!pe)
			return -2;
		L->elem=pe;
		L->listsize+=LISTINCREMENT;
	}
	pe1=pe+i-1;
	pe+=L->length;
	while(pe>pe1)
		*pe--=*pe;
	*pe1=e;
	L->length++;
	return 0;
}

int ListDelete(SqList* L, int i, ElemType* pea)
{
	ElemType *pe, *pe1;
	if(i<1 || i>L->length)
		return -1;
	pe=L->elem+i-1;
	pe1=L->elem+L->length-1;
	pea&&(*pea=*pe);
	while(pe<pe1)
		*pe++=*pe;
	L->length--;
	return 0;
}

void PrintList(SqList* L)
{
	ElemType *pe=L->elem, *pe1=pe+L->length-1;
	while(pe<=pe1)
		printf("%d ", *pe++);
	printf("\n");
}

void PrintListInfo(SqList* L)
{
	printf("L.elem = 0x%08X \nL.length = %d \nL.listsize = %d \n", L->elem, L->length, L->listsize);
}

void SortList(SqList* L)
{
	mSqList mL;
	ElemType temp, pivot, *tail, *left, *right, *pe;
	mL.elem=L->elem;
	mL.length=L->length;
	void partition(mSqList* mL)
	{
		left=mL->elem;
		right=left+mL->length-1;
		tail=left;
		pivot=*right;
		for(pe=left; pe<=right; pe++)
			if(*pe<=pivot){
				temp=*tail;
				*tail++=*pe;
				*pe=temp;
			}
		tail--;
	}
	void quicksort(mSqList* mL)
	{
		if(mL->length<2)
			return;
		partition(mL);
		mSqList mL1, mL2;
		mL1.elem=left;
		mL1.length=tail-left;
		mL2.elem=tail+1;
		mL2.length=right-tail;
		quicksort(&mL1);
		quicksort(&mL2);
	}
	quicksort(&mL);
}

int MessList(SqList* L)
{
	ElemType *a, *b;
	int len=L->length;
	a=(ElemType*)malloc(L->listsize*sizeof(ElemType));
	b=(ElemType*)malloc(len*sizeof(ElemType));
	if(!a||!b)
		return -1;
	memset(b,0,len*sizeof(ElemType));
	int f(int x)
	{
		return x;
	}
	pranda(a, len, &f);
	ElemType* pe=L->elem;
	int i, j;
	for(i=0;i<len;i++){
		for(j=i+1;j<len;j++)
			if(*(a+i)>*(a+j))
				(*(b+i))++;
			else
				(*(b+j))++;
		*(a+i)=*(pe+*(b+i));
	}
	L->elem=a;
	free(pe);
	free(b);
	return 0;
}

void ReverseList(SqList* L)
{
	ElemType *p, *q, t;
	p=L->elem;
	q=p+L->length-1;
	while(p<q){
		t=*p;
		*p++=*q;
		*q--=t;
	}
}

int CloneList(SqList* Ln, SqList* L)
{
	ElemType* pe;
	pe=(ElemType*)malloc(L->listsize*sizeof(ElemType));
	if(!pe)
		return -1;
	Ln->elem=pe;
	Ln->length=L->length;
	Ln->listsize=L->listsize;
	ElemType *p=L->elem, *end_=L->elem+L->length;
	while(pe<end_)
		*pe++=*p++;
	return 0;
}

int ListTraverse(SqList* L, int (*visit)(ElemType*))
{
	ElemType* pe=L->elem;
	int i, len=L->length, ret;
	for(i=1;i<=len;i++,pe++){
		ret=visit(pe);
		if(ret)
			return ret;
	}
	return 0;
}

int fprintList(SqList* L, char* filename, char* openmode)
{
	FILE* fp;
	ElemType* pe;
	int i, len;
	fp=fopen(filename, openmode);
	if(!fp)
		return ferror(fp);
	pe=L->elem;
	len=L->length;
/*	if(strchr(openmode, 'b'))
		if( fwrite(pe, len*sizeof(ElemType), 1, fp)<=0 )
			return ferror(fp);
	else
*/		for(i=0;i<len;i++,pe++)
			if((fprintf(fp,"%d ",*pe))<=0)
				return ferror(fp);
	if(fclose(fp))
		return ferror(fp);
	return -520;
}

int fscanList(SqList* L, char* filename, char* openmode)
{
	FILE* fp;
	ElemType e;
	fp=fopen(filename, openmode);
	if(!fp)
		return ferror(fp);
/*	if(strchr(openmode, 'b'))
		while( fread(&e, sizeof(ElemType), 1, fp)==1 ){
			ListInsert(L, L->length+1, e);
				if( feof(fp) )
					break;
		}
	else
*/		while( fscanf(fp,"%d",&e)>0 ){
			ListInsert(L, L->length+1, e);
			if( feof(fp) )
				break;
		}
	if(fclose(fp))
		return ferror(fp);
	return -520;
}
























#endif