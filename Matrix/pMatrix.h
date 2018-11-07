#ifndef _PMATRIX_H_
#define _PMATRIX_H_

#ifndef _INC_STDLIB
#include <stdlib.h>
#ifndef _INC_STDLIB
#define _INC_STDLIB
#endif
#endif

int __MATRIX__;

typedef struct{
	int row;
	int col;
	double** bp;
}MATRIX;

int InitMatrix(MATRIX* mat, int row, int col)
{
	int i;
	double** bp;
	bp=(double**)malloc(row*sizeof(double*));
	if(!bp)
		return -1;
	mat->bp=bp;
	for(i=0;i<row;i++){
		*(bp+i)=(double*)malloc(col*sizeof(double));
		if(!*(bp+i))
			return i+1;
	}
	mat->row=row;
	mat->col=col;
	return 0;
}

void DestroyMatrix(MATRIX* mat)
{
	int i, row;
	double** bp;
	row=mat->row;
	bp=mat->bp;
	for(i=0;i<row;i++)
		free(*(bp+i));
	free(bp);
}

void PrintMatrix(MATRIX* mat)
{
	int i, j, row, col;
	double **bp, *p;
	bp=mat->bp;
	row=mat->row;
	col=mat->col;
	for(i=0;i<row;i++){
		p=*(bp+i);
		for(j=0;j<col;j++)
			printf("%-8.6G ", *(p+j));
		printf("\n");
	}
}

int MatrixTraverse(MATRIX* mat, int (*visit)(double*, int, int))
{
	int i, row, ret;
	double **bp;
	bp=mat->bp;
	row=mat->row;
	for(i=0;i<row;i++){
		ret=visit(*(bp+i), i, mat->col);
		if(ret)
			return ret;
	}
	return 0;
}

int InverseNum(int* a, int n)
{
	int *p, *q, *t=a+n-1, num=0;
	for(p=a+1;p<=t;p++)
		for(q=a;q<p;q++)
			if(*q>*p)
				num++;
	return num;
}

#ifndef _PDETVALUEX_
double DetValue(MATRIX* mat)
{
	double** bp=mat->bp;
	double det=0, product;
	int order=mat->row;
	if(mat->col!=order){
		__MATRIX__=-1;
		return 0;
	}
	int arr[order+2], *a=arr+1, *t=a+order-1, *p, *q, *r, *s, i, x=0x2, w=1, v=1;
	for(p=a;p<=t;p++)
		*p=p-a;
	arr[0]=-1;
	a[order]=-1;
	do{
		for(p=a,product=1,i=0; p<=t; p++,i++)
			product*=*(*(bp+i)+*p);
		p=t, w=1;
		while(*p<*--p)
			w++;
		if(x&=3, (x+=1)&2)
			det+=product;
		else
			det-=product;
		(w-v-1)/2%2==1 ? ( x=((x&2)==0 ? 2 : 0)) : 0;
		if(w>=order)
			break;
		v=w, q=p;
		while(*++q>*p);
		i=*--q, *q=*p, *p=i;
		p++, q=t;
		while(p<q)
			i=*p, *p++=*q, *q--=i;
	}while(1);
	__MATRIX__=0;
	return det;
}

#else

double DetValue(MATRIX* mat)
{
	double** bp=mat->bp;
	double det=0, product;
	int order=mat->row;
	if(mat->col!=order){
		__MATRIX__=-1;
		return 0;
	}
	int arr[order+2], *a=arr+1, *t=a+order-1, *p, *q, i;
	for(p=a;p<=t;p++)
		*p=p-a;
	arr[0]=-1;
	a[order]=-1;
	int NextOrdinal()
	{
		p=t;
		while(*p<*--p);
		if(p<a)
			return -1;
		q=p;
		while(*++q>*p);
		i=*--q, *q=*p, *p=i;
		p++, q=t;
		while(p<q)
			i=*p, *p++=*q, *q--=i;
		return 0;
	}
	do{
		for(p=a,product=1,i=0; p<=t; p++,i++)
			product*=*(*(bp+i)+*p);
		if(InverseNum(a, order)%2==0)
			det+=product;
		else
			det-=product;
	}while(NextOrdinal()>=0);
	__MATRIX__=0;
	return det;
}
#endif











#endif