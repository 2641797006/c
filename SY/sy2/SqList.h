#ifndef _PPSQLIST_H_
#define _PPSQLIST_H_

#ifndef ElemType
#define ElemType int
#endif

namespace ppSqList{

//#define new new(std::nothrow)
#define CopyElem(dest, src) memcpy(dest, src, sizeof(*(src)))
#define LIST_INIT_SIZE	0
#define LISTINCREMENT	64

int _PPSQLIST_;

class SqList{
	public:
		ElemType* elem;

		SqList();
		SqList(int size);
		SqList(const SqList* L);
		~SqList();

		inline int Length();
		inline void Clear();
		inline ElemType* Insert(ElemType* pe);
		ElemType* Insert(int i, ElemType* pe);
		inline ElemType* Delete(int i);
		ElemType* Delete(int i, ElemType* pe);
		void Print(void (*PrintElem)(ElemType*));

	private:
		int length;
		int listsize;
};

SqList::SqList()
{
	elem=new ElemType[LIST_INIT_SIZE];
	length=0;
	listsize=LIST_INIT_SIZE;
}

SqList::SqList(int size)
{
	elem=new ElemType[size];
	length=0;
	listsize=size;
}

SqList::SqList(const SqList* L)
{
	elem=new ElemType[L->listsize];
	length=L->length;
	listsize=L->listsize;
	memcpy(elem, L->elem, L->length*sizeof(ElemType));
}

SqList::~SqList()
{
	delete[] elem;
	length=0;
	listsize=0;
}

inline int SqList::Length()
{
	return length;
}

inline void SqList::Clear()
{
	length=0;
}

inline ElemType* SqList::Insert(ElemType* pe)
{
	return Insert(length+1, pe);
}

ElemType* SqList::Insert(int i, ElemType* pe)
{
	ElemType* p;
	ElemType *pe0, *pe1;
	if(i<1||i>length+1)
		return NULL;
	if(length>=listsize){
		p=new ElemType[listsize+LISTINCREMENT];
		memcpy(p, elem, length*sizeof(ElemType));
		delete[] elem;
		elem=p;
	}
	pe1=elem+i-1;
	pe0=elem+length;
	while(pe0>pe1)
		CopyElem(pe0, --pe0);
	CopyElem(pe1, pe);
	length++;
	return pe1;
}

inline ElemType* SqList::Delete(int i)
{
	return Delete(i, NULL);
}

ElemType* SqList::Delete(int i, ElemType* pe)
{
	ElemType *pe0, *pe1;
	if(i<1||i>length)
		return NULL;
	pe0=elem+i-1;
	pe1=elem+length-1;
	pe&&CopyElem(pe, pe0);
	do
		CopyElem(pe0, pe0+1);
	while(++pe0<pe1);
	length--;
	return elem+i-1;
}

void SqList::Print(void (*PrintElem)(ElemType*))
{
	ElemType *p, *q;
	p=elem, q=elem+length-1;
	while(p<=q)
		PrintElem(p++);
	std::cout<<std::endl;
}

/*namespace*/ }

#endif