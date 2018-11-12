#ifndef _PPLNODE_H_
#define _PPLNODE_H_

#ifndef ElemType
#define ElemType int
#endif

namespace ppLNode{

//#define new new(std::nothrow)
#define CopyElem(dest, src) memcpy(dest, src, sizeof(*(src)))
int _PPLNODE_;

class LNode{
	public:
		ElemType data;

		LNode();
		LNode(int n);
		LNode(const LNode* L);

		void Destroy();
		inline LNode* getnext();
		inline int Length();
		int Length(LNode** pp);
		inline LNode* GetElem(int i);
		LNode* GetElem(int i, ElemType* pe);
		inline LNode* Insert(ElemType* pe);
		LNode* Insert(int i, ElemType* pe);
		inline LNode* Delete(int i);
		LNode* Delete(int i, ElemType* pe);
		void Print(void (*PrintElem)(ElemType*));

	private:
		LNode* next;

};

LNode::LNode()
{
	next=NULL;
}

LNode::LNode(int n)
{
	int i;
	LNode* p;
	next = n>0 ? new LNode : NULL;
	p=next;
	for(i=1;i<n;i++){
		p->next=new LNode;
		p=p->next;
	}
	if(p)
		p->next=NULL;
}

LNode::LNode(const LNode* L)
{
	CopyElem(&data, &L->data);
	next=L->next;
}

void LNode::Destroy()
{
	LNode *p=next, *q;
	next=NULL;
	while(p){
		q=p;
		p=p->next;
		delete q;
	}
}

inline LNode* LNode::getnext()
{
	return next;
}

inline int LNode::Length()
{
	return Length(NULL);
}

int LNode::Length(LNode** pp)
{
	int len=0;
	if(!next)
		return 0;
	LNode* p=next;
	while(p){
		len++;
		p=p->next;
	}
	if(pp)
		*pp=p;
	return len;
}

inline LNode* LNode::GetElem(int i)
{
	return GetElem(i, NULL);
}

LNode* LNode::GetElem(int i, ElemType* pe)
{
	if(i<1||!next)
		return NULL;
	LNode* p=next;
	while(p){
		if(--i<=0){
			if(pe)
				CopyElem(pe, &p->data);
			return p;
		}
		p=p->next;
	}
	return NULL;
}

inline LNode* LNode::Insert(ElemType* pe)
{
	return Insert(Length()+1, pe);
}

LNode* LNode::Insert(int i, ElemType* pe)
{
	LNode *p, *q;
	q=new LNode;
	CopyElem(&q->data, pe);
	if(i==1){
		q->next=next;
		next=q;
		return q;
	}
	p=GetElem(i-1);
	if(!p)
		return NULL;
	q->next=p->next;
	p->next=q;
	return q;
}

inline LNode* LNode::Delete(int i)
{
	return Delete(i, NULL);
}

LNode* LNode::Delete(int i, ElemType* pe)
{
	LNode *p, *q;
	_PPLNODE_=0;
	if(!next)
		return NULL;
	if(i==1){
		p=next;
		next=next->next;
		delete p;
		_PPLNODE_=-1;
		return NULL;
	}
	p=GetElem(i-1);
	if(!p||!p->next)
		return NULL;
	q=p->next;
	if(pe)
		CopyElem(pe, &q->data);
	p->next=q->next;
	delete q;
	return p;
}

void LNode::Print(void (*PrintElem)(ElemType*))
{
	if(!next)
		return;
	PrintElem(&next->data);
	LNode* p=next;
	while(p=p->next)
		PrintElem(&p->data);
	printf("\n");
}

}

#endif