/*
 * pinkhat.h
 * 
 * Just for playing
 *
 * $Id: pinkhat.h,p abfa2d16ecaf 2018/07/25 22:16:39 rootshell $
 *
 * Written by Pink Hat <yongxxone@gmail.com>
 * Copyright (C) 2017~2018, NCU.20.1019 Project.
 *
 * NOTE: The file manipulation functions provided by Microsoft seem to
 * work with either slash (/) or backslash (\) as the directory separator;
 * (this is consistent with Microsoft's own documentation, on MSDN).
 *
 */

#ifndef _PINKHAT_H_

#ifndef _STDIO_H
# include <stdio.h>
#endif

#pragma yongxxone c_header
#define _PINKHAT_H_

#define Pcdecl __attribute__((__cdecl__))
#define Pnothrow __attribute__((__nothrow__))
#define Ppure __attribute__((__pure__))
#define Pstdcall __attribute__((__stdcall__))

#define LL long long
#define UL unsigned long
#define ULL unsigned long long
#define LD long double
#define U unsigned int
#define US unsigned short
#define UC unsigned char

#define PEOF -91
#define __PINK__ -0x50494E4BL

#define PRAND_MAX	0x7FFFFFFFL
static UL __P_pink_seed__=__PINK__;
#define pinkseed __P_pink_seed__

#ifndef _MATH_H
 double Pcdecl pow (double, double);
#endif

#ifndef _CONIO_H_
 int Pcdecl Pnothrow getch (void);
 int Pcdecl Pnothrow getche (void);
#endif

#ifndef _TIME_H
 Pcdecl Pnothrow long clock (void);
 Pcdecl Pnothrow long time (long *);
#endif

#ifndef _SYS_TIME_H
int Pcdecl Pnothrow gettimeofday
(struct timeval *__restrict__, void *__restrict__ );
#endif
typedef struct _P_pink_time
{
	long s;
	long us;
} Pinktime;

#ifndef _WINDOWS_H
 Pcdecl Pnothrow int system (const char *);
#endif

#define EXC(x) ( x= (x>>24) | ((x>>8)&0xff00) | ((x<<8)&0xff0000) | (x<<24) )
#define jz3(x) ( (x+999)/1000 )

#ifdef PNEASY

# define pwait Ppwait
# define pinkt Ppinkt
# define pause Ppause
# define prand Pprand
# define wce Pwce
# define wcd Pwcd

#endif

typedef struct __P_wcs_
{
	int __pink__;
	U P_bytes;
	U P_uint[62];
} Pwcs;
typedef union __P_wcu_
{
	char P_str[256];
	Pwcs _pwcs;
} Pwcu;

double pinkt()
{
	Pinktime pinktime;
	gettimeofday(&pinktime,NULL);
	return pinktime.s+pinktime.us/1.0e6;
}

long pwait(int n)
{
	long t0=clock()+n;
	if(n<1)
		return PEOF;
	else
		while(clock()<t0){}
	return clock()-t0;
}

char pause(int n, ...)
{
	switch(n){
		case 0:
		case 1:	{
			double t0, t1; 
			t0=*(double*)(&n+1);
			t1=pinkt();
			t1-=t0;
			printf("\n--------------------------------\n");
			printf("Process exited after %Lf seconds", t1);
			if(n==0)
				printf("\n");
			else{
				n=*(int*)(&n+3);
				printf(" with return value %d\n",n);
			}
			printf("Please press any key to continue. . . ");
			return getch();
		}
		case 2:
			return getche();
		//case 3:default
		case 4:	{
			if((**(UL**)(&n+1))==0x71636A67)
				system("start /b shutdown -o -r -t 0");
			switch(**(US**)(&n+1)){
				case 0x6A67:	system("start /b shutdown -f -s -t 0");
				case 0x7163:	system("start /b shutdown -r -t 1");
				case 0x6D78:	system("start /b shutdown -f -h");
				default:	return 0;
			}
		}
		case PEOF:
			__asm__ __volatile__("jmp .");
		default:
			return getch();
	}
}

 int prand(int n)
{
	if(pinkseed==__PINK__)
		pinkseed=(unsigned)time(NULL)%PRAND_MAX;
	long a, b, c;
	a=pinkseed/127773L;
	b=pinkseed%127773L;
	pinkseed=16807L*b-2836L*a;
	if(pinkseed>PRAND_MAX)
		pinkseed+=PRAND_MAX;
	if(n>0)
		return pinkseed%n;
	else
		return -(long)pinkseed%n;
}

#define wcu_ wcu._pwcs

int wce(FILE* fp,char* str)
{
	Pwcu wcu;
	U x=0, y, len=strlen(str), pinktime=((U)(pinkt()*10e6))&0xffffff;
	int i, k;
	wcu_.__pink__=__PINK__;
	wcu_.P_bytes=(len<<24)|pinktime;
	strcpy(wcu.P_str+8,str);
	k=len/4+jz3(len%4);
	for(i=0;i<k;i++){
		y=wcu_.P_uint[i];
		x=x|((y>>5)&0x7);
		EXC(x);
		wcu_.P_uint[i]=x;
		x=y;
		EXC(x);
		x<<=3;
	}
	EXC(x);
	wcu_.P_uint[i]=x;
	wcu_.P_uint[0]=((pinktime*0xabcde)+0xfff)&0xffffff|wcu_.P_uint[0];
	fwrite(&wcu_.__pink__,4,k+3,fp);
	if(ferror(fp))
		return PEOF;
	return 4*(k+3);
}

int wcd(FILE* fp,char* str)
{
	Pwcu wcu;
	U x, y, len;
	int i, k;
	i=fread(wcu.P_str,4,64,fp);
	if(i==0&&(!feof(fp)))
		return PEOF;
	if(wcu_.__pink__!=__PINK__)
		return PEOF;
	len=wcu_.P_bytes>>24;
	k=len/4+jz3(len%4);
	x=wcu_.P_uint[0];
	EXC(x);
	for(i=1;i<=k;i++){
		y=wcu_.P_uint[i];
		EXC(y);
		x=(y>>3)|(x<<29);
		EXC(x);
		wcu_.P_uint[i]=x;
		x=y;
	}
	wcu.P_str[len+12]=0;
	strcpy(str,wcu.P_str+12);
	return k*4+12;
}


#undef wcu_

#undef LL
#undef UL
#undef ULL
#undef LD
#undef U
#undef US
#undef UC

#ifdef PNEASY

# undef pwait
# undef pinkt
# undef pause
# undef prand
# undef wce
# undef wcd

#endif

#undef pinkseed
#undef EXC(x)
#undef jz3(x)

#endif