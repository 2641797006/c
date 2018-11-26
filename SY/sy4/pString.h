#ifndef _PSTRING_H_
#define _PSTRING_H_

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif

#ifndef _INC_STRING
#include <string.h>
#endif

#ifndef _INC_CONIO
#include <conio.h>
#endif

// try not to use this function
int getstr(char* buffer, int size, char delim)
{
	int i, j;
	if(!buffer || size<1)
		return 0;
	for(i=0;i<size;i++){
		*buffer=getch();	//here may waste lots of time
		if(*buffer==delim)
			break;
		*buffer=='\x0d' ? (*buffer-=3) : 0;
		if(*buffer!='\b')
			putchar(*buffer++);
		else{
			if(i-->0){
				buffer--, i--;
				putchar('\b'), putchar(' '), putchar('\b');
			}
		}
	}
	return i;
}

int putstr(char* buffer, int size, char delim)
{
	int i;
	if(size<1)
		return 0;
	for(i=0;i<size;i++){
		if(*buffer==delim)
			break;
		putchar(*buffer++);
	}
	return i;
}

#endif