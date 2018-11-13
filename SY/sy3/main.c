#include <stdio.h>
#include <math.h>
#include <C:/Users/26417/Desktop/SqStack/pSqStackX.h>
#include <C:/Users/26417/Desktop/SqStack/Pexpress.h>

#define ResetCin() ( stdin->_cnt=0, stdin->_ptr=stdin->_base )

int main(int argc, char** argv)
{
	InitStack();
	QWORD* bp;

	int n, ret, len;
	double d, result;
	char str[2304], tail_buf[4096], *tail=tail_buf+1, *ps=str, *pt=tail;
	*tail_buf='\n';
	printf("WH::中缀表达式计算\n官网: https://2641797006.github.io/html/\n开源: https://2641797006.github.io/html/project/SqStack.html\n\n");

	while(1)
	{
		ResetCin();
		n=0, *str=0, *tail=0;
		ps=str, pt=tail_buf;
		printf(">>> ");

		ret=scanf("%4000[^\n]%n", tail, &n);
		if(n==0||ret<=0)
			continue;
		len=n+1;
		do{
			sscanf(pt, "%*[^0-9.+*-/^()]%n", &n);
			pt+=n;
			if((len-=n)<=0)
				break;
			sscanf(pt, "%256[0-9.+*-/^()]%n", ps, &n);
			pt+=n;
			if((len-=n)<=0)
				break;
			ps+=strlen(ps);
			if(strlen(str)>2000)
				break;
		}while(*pt!='\0');
		if(strlen(str)==0)
			continue;

		*tail=0;
		bp=GetTopP();
		if( InfixToSuffix(str, tail)!=0 )
			continue;
		SetTopP(bp);

		if(argc>1){
			printf("中缀表达式: %s\n", str);
			printf("后缀表达式: %s\n", tail);
		}
		bp=GetTopP();
		result=DealSuffix(tail);
		SetTopP(bp);

		printf("%.16G\n", result);

	}
}


