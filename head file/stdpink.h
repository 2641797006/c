#ifndef _STDPINK_H_
#define _STDPINK_H_

/*
#ifndef _IO_H
 Pcdecl Pnothrow int access (const char*, int);
#endif
# define PF_OK	0	// Check for file existence
# define PX_OK	1	// MS access() doesn't check for execute permission.
# define PW_OK	2	// Check for write permission
# define PR_OK	4	// Check for read permission
*/

#ifndef _PINKHAT_H_
#define PEOF -91
#endif

#define LL long long
#define UL unsigned long
#define ULL unsigned long long
#define LD long double
#define U unsigned int
#define US unsigned short
#define UC unsigned char


typedef char *__pink_va_list;
typedef __pink_va_list Ppinkval;
#define pinkval Ppinkval

#define _pink_full_int(x) ( ( sizeof(x)+sizeof(int)-1 ) & ~( sizeof(int)-1 ) )
#define Ppinkfint(x) _pink_full_int(x)
#define pinkfint(x) Ppinkfint(x)

#define _pink_va_start(p,v) ( p= (pinkval)&v + pinkfint(v) )
#define Ppva_start(p,v) _pink_va_start(p,v)
#define pva_start(p,v) Ppva_start(p,v)

#define _pink_va_arg(p,t) ( *(t*) ( (p+=pinkfint(t)) - pinkfint(t) ) )
#define Ppva_arg(p,t) _pink_va_arg(p,t)
#define pva_arg(p,t) Ppva_arg(p,t)

#define _pink_va_end(p) ( p=(pinkval)0 )
#define Ppva_end(p) _pink_va_end(p)
#define pva_end(p) Ppva_end(p)

LD abv(LD num);

int ascstr()
{
	char str[32];
	int i, len;
	scanf("%[^\n]%n%*c", str, &len);
	for(i=0;i<len;i++)
		printf("%02hhX ", *(str+i));
}

int leap(LL year)
{
	if(year%400==0)
		return 1;
	else if(year%4==0&&year%100!=0)
		return 1;
	else
		return 0;
}

LL jc(int num)
{
	int i, sym=1;
	LL r=1;
	if(num<0){
		sym=-1;
		num=-num;
	}
	for(i=2;i<=num;i++)
		r*=i;
	if(sym<0)
		r=-r;
	return r;
}

int jpri(LL num)
{
	U i, k;
	if(num==1||num==0||num==-1)
		return -91;
	k=abv(pow(num,0.5));
	for(i=2;i<=k;i++)
		if(num%i==0)
			return 1;
	return 0;
}

LD abv(LD num)
{
	if(num<0)
		return -num;
	else
		return num;
}

#undef LL
#undef UL
#undef ULL
#undef LD
#undef U
#undef US
#undef UC

#endif