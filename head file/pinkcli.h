#ifndef _PINKCLI_H_
#define _PINKCLI_H_

#ifndef _INC_STDLIB
#include <stdlib.h>
#ifndef _INC_STDLIB
#define _INC_STDLIB
#endif
#endif

HANDLE Phstdout=NULL;

#define pColorInit() Phstdout=GetStdHandle(STD_OUTPUT_HANDLE);

void PColor(int x)
{
/*	char str[32];
	x>=0 ?: (x=0xf);
	x<=0xff ?: (x=0xf);
	sprintf(str, "color %02x 2>nul", x);
	system(str);
*/
	SetConsoleTextAttribute(Phstdout, x);
}

#define pColor(v) PColor(0x##v)











#endif