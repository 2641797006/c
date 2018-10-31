#ifndef _LNODEM_H_
#define _LNODEM_H_

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
typedef int (*COMPARE)(ElemType*, ElemType*);

typedef struct LNode{
	ElemType data;
	struct LNode* next;
}LNode;

#define CopyElem(dest, src) memcpy(dest, src, sizeof(*(src)))

int InitList(LNode* L, int size)
{
	int i;
	for(i=0;i<size;i++){
		L->next=(LNode*)malloc(sizeof(LNode));
		L=L->next;
		if(!L)
			return -1;
	}
	L->next=NULL;
	return 0;
}

void DestroyList(LNode* L)
{
	LNode* p=L->next;
	L->next=NULL;
	while(p){
		L=p;
		p=p->next;
		free(L);
	}
}

int ListLength(LNode* L)
{
	int i=0;
	while(L->next){
		i++;
		L=L->next;
	}
	_ret_=(QWORD)L;
	return i;
}

LNode* GetElem(LNode* L, int i, ElemType* e)
{
	if(i<0)
		return NULL;
	while(L){
		if(i--<=0){
			if(e)
				CopyElem(e, &L->data);
			return L;
		}
		L=L->next;
	}
	return NULL;
}

int ListTraverse(LNode* L, VISIT visit)
{
	int ret;
	while(L=L->next){
		ret=visit(&L->data);
		if(ret){
			_ret_=(QWORD)L;
			return ret;
		}
	}
	return 0;
}

LNode* LocateElem(LNode* L, VISIT visit)
{
	if( ListTraverse(L, visit) )
		return (LNode*)_ret_;
	return NULL;
}

LNode* PriorElem(LNode* L, ElemType* cur_e, COMPARE compare)
{
	LNode* p;
	while(L->next){
		p=L;
		L=L->next;
		if( compare(cur_e, &L->data)==0 )
			return p;
	}
	return NULL;
}

LNode* ListInsert(LNode* L, int i, ElemType* pe)
{
	LNode *p, *q;
	p=GetElem(L, i-1, NULL);
	if(!p)
		return NULL;
	q=(LNode*)malloc(sizeof(LNode));
	if(!q)
		return NULL;
	CopyElem(&q->data, pe);
	q->next=p->next;
	p->next=q;
	return q;
}

LNode* ListDelete(LNode* L, int i, ElemType* pe)
{
	LNode *p;
	p=GetElem(L, i-1, NULL);
	if(!p||!p->next)
		return NULL;
	L=p->next;
	if(pe)
		CopyElem(pe, &L->data);
	p->next=p->next->next;
	free(L);
	return p;
}

typedef void (*PrintElem)(ElemType*);

void PrintList(LNode* L, PrintElem printelem)
{
	while(L=L->next)
		printelem(&L->data);
	printf("\n");
}

LNode* MergeList(LNode* La, LNode* Lb, COMPARE compare)
{
	LNode *p=La, *q=Lb, *Lc;
	La=La->next;
	Lb=Lb->next;
	if(La==NULL){
		Lc=q;
		return q;
	}
	if(Lb==NULL){
		Lc=p;
		return p;
	}
	Lc = compare(&La->data, &Lb->data)<=0 ? (La=La->next, p) : (Lb=Lb->next, q);
	p=Lc->next;
	while(La!=NULL && Lb!=NULL){
		if(compare(&La->data, &Lb->data)<=0){
			q=La;
			La=La->next;
		}
		else{
			q=Lb;
			Lb=Lb->next;
		}
		p->next=q;
		p=q;
	}
	p->next = La==NULL ? Lb : La;
	return Lc;
}

COMPARE GlobalCompare=NULL;
#define compare GlobalCompare

LNode* MergeList_S(LNode* head, int lenA, LNode* Lb, int lenB)
{
	LNode *La=head->next, *p;
	if( compare(&La->data, &Lb->data)<=0 ){
		p=La;
		La=La->next;
		lenA--;
	}
	else{
		p=Lb;
		Lb=Lb->next;
		lenB--;
	}
	head->next=p;
	while(lenA>0 && lenB>0)
		if( compare(&La->data, &Lb->data)<=0 ){
			p->next=La;
			p=La;
			La=La->next;
			lenA--;
		}
		else{
			p->next=Lb;
			p=Lb;
			Lb=Lb->next;
			lenB--;
		}
	p->next = lenA==0 ? (lenA=lenB, Lb) : La;
	while(lenA-->0)
		p=p->next;
	return p;
}

void SortList(LNode* L)
{
	LNode* MergeSort_R(LNode* head, LNode* end, int len)
	{
		LNode *mid, *p;
		if(head->next==end)
			return end;
		mid=GetElem(head, len/2, NULL);
		p=mid->next;
		mid=MergeSort_R(head, mid, len/2);
		mid->next=p;
		MergeSort_R(mid, end, (len+1)/2);
		end=MergeList_S(head, len/2, mid->next, (len+1)/2);
		return end;
	}
	int length=ListLength(L);
	MergeSort_R(L, GetElem(L, length, NULL), length);
	GetElem(L, length, NULL)->next=NULL;
}

#undef compare

void ReverseList(LNode* L)
{
	LNode *p, *q, *r;
	p=L->next;
	if(!p)
		return;
	q=p->next;
	if(!q)
		return;
	p->next=NULL;
	r=q->next;
	while(r){
		q->next=p;
		p=q;
		q=r;
		r=r->next;
	}
	L->next=q;
	q->next=p;
}

#endif