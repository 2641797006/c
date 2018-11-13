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

double DetValue(MATRIX* mat)
{
	double** bp=mat->bp;
	double det=0, product;
	int order=mat->row;
	if(mat->col!=order){
		__MATRIX__=-1;
		return 0;
	}
	int arr[order+2], *a=arr+1, *t=a+order-1, *p, *q, i, x=0x2, w=1, v=1;
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

MATRIX* TransposeMatrix(MATRIX* mat, MATRIX* rmat)
{
	MATRIX* m;
	if(!rmat){
		m=(MATRIX*)malloc(sizeof(MATRIX));
		if( !m || InitMatrix(m, mat->col, mat->row) )
			return NULL;
	}
	else
		m=rmat;
	int i, j;
	for(i=0;i<m->row;i++)
		for(j=0;j<m->col;j++)
			*(*(m->bp+i)+j)=*(*(mat->bp+j)+i);
	return m;
}

MATRIX* CofactorMatrix(MATRIX* mat, int row, int col, MATRIX* rmat)
{
	row--, col--;
	MATRIX* m;
	if(!rmat){
		m=(MATRIX*)malloc(sizeof(MATRIX));
		if( !m || InitMatrix(m, mat->row-1, mat->col-1) )
			return NULL;
	}
	else
		m=rmat;
	int i, j, r=0, c=0;
	for(i=0;i<mat->row;i++){
		if(i==row){
			r=1;
			continue;
		}
		for(j=0,c=0;j<mat->col;j++){
			if(j==col){
				c=1;
				continue;
			}
			*(*(m->bp+i-r)+j-c)=*(*(mat->bp+i)+j);
		}
	}
	return m;
}

MATRIX* CloneMatrix(MATRIX* mat)
{
	MATRIX* m=(MATRIX*)malloc(sizeof(MATRIX));
	if( !m || InitMatrix(m, mat->row, mat->col) )
		return NULL;
	int i, j;
	for(i=0;i<m->row;i++)
		for(j=0;j<m->col;j++)
			*(*(m->bp+i)+j)=*(*(mat->bp+i)+j);
	return m;
}

void MatrixAdd(MATRIX* m1, MATRIX* m2)
{
	int i, j;
	for(i=0;i<m1->row;i++)
		for(j=0;j<m1->col;j++)
			*(*(m1->bp+i)+j)+=*(*(m2->bp+i)+j);
}

void MatrixSub(MATRIX* m1, MATRIX* m2)
{
	int i, j;
	for(i=0;i<m1->row;i++)
		for(j=0;j<m1->col;j++)
			*(*(m1->bp+i)+j)-=*(*(m2->bp+i)+j);
}

MATRIX* MatrixMul(MATRIX* m1, MATRIX* m2)
{
	if(m1->col!=m2->row)
		return NULL;
	MATRIX* m=(MATRIX*)malloc(sizeof(MATRIX));
	if( !m || InitMatrix(m, m1->row, m2->col) )
		return NULL;
	int i, j, k;
	double product;
	for(i=0;i<m->row;i++)
		for(j=0;j<m->col;j++){
			product=0;
			for(k=0;k<m1->col;k++)
				product+=*(*(m1->bp+i)+k)**(*(m2->bp+k)+j);
			*(*(m->bp+i)+j)=product;
		}
	return m;
}

MATRIX* AdjointMatrix(MATRIX* mat)
{
	int i, j;
	MATRIX *adm, *acm;
	adm=(MATRIX*)malloc(sizeof(MATRIX));
	acm=(MATRIX*)malloc(sizeof(MATRIX));
	i=InitMatrix(adm, mat->row, mat->col);
	j=InitMatrix(acm, mat->row-1, mat->col-1);
	if(!adm||!acm || i||j)
		return NULL;
	for(i=0;i<adm->row;i++)
		for(j=0;j<adm->col;j++)
			*(*(adm->bp+i)+j)=( ((i+j)%2==0) ? 1 : -1 )*DetValue(CofactorMatrix(mat, j+1, i+1, acm));
	DestroyMatrix(acm);
	free(acm);
	return adm;
}

MATRIX* InverseMatrix(MATRIX* mat)
{
	double det;
	MATRIX* m;
	det=DetValue(mat);
	if(det==0)
		return NULL;
	m=AdjointMatrix(mat);
	if(!m)
		return NULL;
	int i, j;
	for(i=0;i<m->row;i++)
		for(j=0;j<m->col;j++)
			*(*(m->bp+i)+j)/=det;
	return m;
}

void PrintMatrixS(MATRIX* mat)
{
	char c;
	int i, j, row, col;
	double **bp, *p, d;
	bp=mat->bp;
	row=mat->row;
	col=mat->col;
	for(i=0;i<row;i++){
		p=*(bp+i);
		for(j=0;j<col;j++){
			*(p+j)<0 ? (c='-', d=-*(p+j)) : (c=' ', d=*(p+j)) ;
			printf("%c%-6.6G ", c, d);
		}
		printf("\n");
	}
}

#endif