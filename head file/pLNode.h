#ifndef _PLNODE_H_
#define _PLNODE_H_

#ifndef _INC_STDLIB
#include <stdlib.h>
#ifndef _INC_STDLIB
#define _INC_STDLIB
#endif
#endif
//malloc(), realloc(), free()

#ifndef ElemType
#define ElemType int
#endif
//ElemType is a Number

typedef struct LNode{
	ElemType data;
	struct LNode* next;
}LNode;

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
	while(L=L->next)
		i++;
	return i;
}

LNode* GetElem(LNode* L, int i, ElemType* e)
{
	if(i<0)
		return NULL;
	while(L){
		if(i--<=0){
			if(e)
				*e=L->data;
			return L;
		}
		L=L->next;
	}
	return NULL;
}

LNode* LocateElem(LNode* L, ElemType e)
{
	while(L=L->next)
		if(L->data==e)
			return L;
	return NULL;
}

LNode* PriorElem(LNode* L, ElemType cur_e, ElemType* pre_e)
{
	LNode* p;
	while(L->next){
		p=L;
		L=L->next;
		if(cur_e==L->data){
			if(pre_e)
				*pre_e=p->data;
			return p;
		}
	}
	return NULL;
}

LNode* ListAmend(LNode* L, ElemType e, ElemType e1)
{
	LNode* p;
	p=LocateElem(L, e);
	if(!p)
		return NULL;
	p->data=e1;
	return p;
}

LNode* ListInsert(LNode* L, int i, ElemType e)
{
	LNode *p, *q;
	p=GetElem(L, i-1, NULL);
	if(!p)
		return NULL;
	q=(LNode*)malloc(sizeof(LNode));
	if(!q)
		return NULL;
	q->data=e;
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
		*pe=L->data;
	p->next=p->next->next;
	free(L);
	return p;
}

void PrintList(LNode* L)
{
	while(L=L->next)
		printf("%d ", L->data);
	printf("\n");
}

void PrintListX(LNode* L)
{
	int i=0;
	printf("head->data=%d\nhead->next=0x%08X \n", L->data, L->next);
	while(L=L->next){
		printf("%8d 0x%08X ", L->data, L->next);
		if(++i%5==0)
			printf("\n");
	}
	printf("\n");
}

LNode* MergeList(LNode* La, LNode* Lb)
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
	Lc = La->data<=Lb->data ? (La=La->next, p) : (Lb=Lb->next, q);
	p=Lc->next;
	while(La!=NULL && Lb!=NULL){
		if(La->data<=Lb->data){
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

LNode* MergeList_S(LNode* head, int lenA, LNode* Lb, int lenB)
{
	LNode *La=head->next, *p;
	if(La->data<=Lb->data){
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
		if(La->data<=Lb->data){
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












#endif