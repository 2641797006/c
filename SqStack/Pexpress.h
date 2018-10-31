#ifndef _PEXPRESS_H_
#define _PEXPRESS_H_

#ifndef _PSQSTACKX_H_
#include <__pink/pSqStackX.h>
#endif

int precede(char c)
{
	int ret;
	switch(c)
	{
		case '^':
			ret=0;
		break;
		case '\2': case '\7':
			ret=1;
		break;
		case '*': case '/':
			ret=2;
		break;
		case '+': case '-':
			ret=3;
		break;
		case ')':
			ret=4;
		break;
		case '(':
			ret=5;
		break;
		case '#':
			ret=6;
		break;
		default:
			ret=0xffff;
	}
	return ret;
}

int InfixToSuffix(char* infix, char* suffix)
{
	char *pin=infix, *psuf=suffix, c;
	int n, signs=0, yx;
	double d;
	push('#');
	while(*pin!='\0')
	{
		if(0x30<=*pin&&*pin<=0x39){
			sscanf(pin, "%Lf%n", &d, &n);
			pin+=n;
			sprintf(psuf, "%.20G@%n", d, &n);
			psuf+=strlen(psuf);
			signs=1;
			continue;
		}
		switch(*pin)
		{
			case '(':
				push(*pin);
				signs=0;
			break;
			case ')':
				yx=precede(*pin);
				do{
					GetTop(&c);
					if(precede(c)<=yx)
						pop(psuf++);
					else
						break;
				}while(1);
				pop(psuf);
				if(*psuf!='(')
					return -1;
				signs=1;
			break;
			case '+': case '-':
				if(!signs){
					if(*pin=='-')
						push('\2');
					else
						push('\7');
					signs=0;
					break;
				}
/*				yx=precede(*pin);
				do{
					GetTop(&c);
					if(precede(c)<=yx)
						pop(psuf++);
					else
						break;
				}while(1);
				push(*pin);
				signs=0;			
			break;
*/			case'*': case'/': 
				yx=precede(*pin);
				do{
					GetTop(&c);
					if(precede(c)<=yx)
						pop(psuf++);
					else
						break;
				}while(1);
				push(*pin);
				signs=0;
			break;
			case '^':
				yx=precede(*pin);
				do{
					GetTop(&c);
					if(precede(c)<yx)
						pop(psuf++);
					else
						break;
				}while(1);
				push(*pin);
				signs=0;
			break;
			default:
				return -10;
		}
		pin++;
	}
	do{
		pop(psuf);
	}while(*psuf++!='#');
	*psuf='\0';
	return 0;
}

double HandleSuffix(char* suffix)
{
	int n;
	double result=0, d;
	char* psuf=suffix;
	QWORD* bp;
	bp=GetTopP();
	while(*psuf!='#')
	{
		if(0x30<=*psuf&&*psuf<=0x39){
			sscanf(psuf, "%Lf%*c%n", &result, &n);
			psuf+=n;
			push(result);
			continue;
		}
		pop(&d);
		if(GetTopP()<bp)
			return 0;
		pop(&result);
		switch(*psuf)
		{
			case '+':
				result+=d;
			break;
			case '-':
				result-=d;
			break;
			case '*':
				result*=d;
			break;
			case '/':
				result/=d;
			break;
			case '^':
				result=pow(result,d);
			break;
			case '\7': case '\2':
				push(result);
				result= *psuf=='\7' ? d : -d;
			break;
			default:;
		}
		psuf++;
		push(result);
	}
	return result;
}





















#endif