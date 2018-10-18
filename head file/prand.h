#ifndef _PRAND_H_
#define _PRAND_H_

#ifndef _TIME_H_
#include <time.h>
#ifndef _TIME_H_
#define _TIME_H_
#endif
#endif

#define __PINK__ 	-0x50494E4BL
#define PRAND_MAX	0x7FFFFFFFL

/* 16807=7^5, 127773=PRAND_MAX/16807, 2836=PRAND_MAX%127773 */
int prand()
{
	static unsigned long seed=__PINK__;
	if(seed==__PINK__)
		seed=(unsigned)time(NULL);
	long a, b;
	a=seed/127773L;
	b=seed%127773L;
	seed=16807L*b-2836L*a;
	if(seed>PRAND_MAX)
		seed+=PRAND_MAX;
	return seed;
}

void pranda(int* a, int x, int (*f)(int))
{
	int *p=a+x-1;
	for(;p>=a;p--)
		*p=f(prand());
}

void prandd(double* a, int x, double (*f)(int))
{
	double *p=a+x-1;
	for(;p>=a;p--)
		*p=f(prand());
}

int prandx()
{
	static unsigned long seed=__PINK__;
	if(seed==__PINK__)
		seed=(unsigned)time(NULL);
	long a, b;
	a=seed/255546L;
	b=seed%255546L;
	seed=16807L*b-5673L*a;
	return seed;
}

void prandax(int* a, int x, int (*f)(int))
{
	int *p=a+x-1;
	for(;p>=a;p--)
		*p=f(prandx());
}

void pranddx(double* a, int x)
{
	double *p=a+x-1;
	typedef union all{
		int a[2];
		double d;
	}all;
	all t;
	for(;p>=a;p--){
		t.a[0]=prandx();
		t.a[1]=prandx();
		*p=t.d;
	}
}

int phit(double x)
{
	if(x*10000>prand()%10000)
		return 1;
	else
		return 0;
}

#undef __PINK__

#endif