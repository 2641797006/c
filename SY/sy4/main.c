#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <__pink/ptype.h>
#include <__pink/pfile.h>
#include <C:\Users\26417\Desktop\string\pString.h>

#define ResetCin() rewind(stdin)
#define isvchar(_Char) ( _Char=='_' || isdigit(_Char) || isupper(_Char) || islower(_Char) )

void menu();
char choose(char c);
BOOL WINAPI CtrlProc(DWORD dwCtrlType);

FILE *fp;
char *buffer, *filepath, *target;

int main()
{
	SetConsoleCtrlHandler(CtrlProc, TRUE);

	char *ptr;
	int length;
	int bufsiz=0x10;
	int getsiz=8;
	int bufadd=0x10;

	int i, j, len, row;

	char *env, *pc, *pc1, *pc2, *pc3, c;
	char *dir[3]={"/desktop", "/wh_", "/"};
	env=getenv("USERPROFILE");
	filepath=malloc(0x400);
	buffer=malloc(bufsiz);
	target=malloc(0x400);
	if(!filepath||!buffer||!target)
		return -1;
	ptr=buffer, length=0;
	strcpy(filepath, env);
	strcat(filepath, dir[0]);
	strcat(filepath, dir[1]);
	strcat(filepath, getenv("USERNAME"));
	mkdir(filepath);
	strcat(filepath, dir[2]);
	strcat(filepath, getenv("USERNAME"));
	strcat(filepath, ".txt");
	fp=fopen(filepath, "w+");
	printf("WH::Դ����: https://2641797006.github.io/html/\n\n");

	while(1)
	{
		menu();
		ResetCin();
		ungetc(' ', stdin);
		if( scanf("%*[^0-9a-zA-Z]%1[0-9a-zA-Z]", &i)<1 )
			continue;
		i=choose(i);
		switch(i)
		{
			case 'A':
				printf("���ļ���������(\"Ctrl+S\"����):\n");
				while(1){
					if(bufsiz-length<getsiz){
						pc=realloc(buffer, bufsiz+bufadd);
						if(!pc)
							return ~'A'+1;
						buffer=pc, bufsiz+=bufadd, ptr=buffer+length;
					}
					i=getstr(ptr, getsiz, '\x13');
					ptr+=i, length+=i;
					if(i<getsiz)
						break;
				}
				putchar('\n');
				*ptr=0;
			break;
			case 'B':
				puts(buffer);
			break;
			case 'C':
				printf("������Ҫ���ҵ��ַ���: ");
				ResetCin();
				ungetc('\n', stdin);
				scanf("%*[\n]%64[^\n]", target);
				pc=buffer, j=0;
				while(pc<ptr && (pc=strstr(pc, target)))
						j++, pc++;
				printf(">>>���ҵ� %d �� \"%s\"\n\n", j, target);
			break;
			case 'D':
				printf("������Ҫ���ҵ��ַ���: ");
				ResetCin();
				ungetc('\n', stdin);
				scanf("%*[\n]%64[^\n]", target);
				i=strlen(target);
				pc=buffer, j=0;
				while(pc<ptr && (pc=strstr(pc, target))){
					if( (pc==buffer || !isvchar(*(pc-1))) && (!*(pc+i) || !isvchar(*(pc+i))) )
						j++;
					pc++;
				}
				printf(">>>���ҵ� %d �� \"%s\"\n\n", j, target);
			break;
			case 'E':
				printf("������Ҫ���ҵ��ַ���: ");
				ResetCin();
				ungetc('\n', stdin);
				scanf("%*[\n]%64[^\n]", target);
				i=0, j=0, row=1;
				pc=buffer, pc1=pc;
				while(pc=strstr(pc, target)){
					c=*pc, *pc=0;
					while(pc3=strchr(pc1, '\n'))
						row++, pc1=pc3+1;
					pc2= row>1 ? pc1-1 : pc1, j=0;
					while(pc3=strchr(pc2, '\t'))
						j++, pc2=pc3+1;
					*pc=c, i++, pc++;
					printf("%d. ��%d��, ��%d��\n", i, row, pc-pc1+j*7);
				}
				printf("���ҵ�%d�� \"%s\"\n", i, target);
			break;
			case 'F':
				printf("������Ҫ���ҵ��ַ���: ");
				ResetCin();
				ungetc('\n', stdin);
				scanf("%*[\n]%64[^\n]", target);
				i=0, j=0, row=1;
				len=strlen(target);
				pc=buffer, pc1=pc;
				while(pc=strstr(pc, target)){
					c=*pc, *pc=0;
					while(pc3=strchr(pc1, '\n'))
						row++, pc1=pc3+1;
					pc2=row>1 ? pc1-1 : pc1;
					j=0;
					if( (pc==buffer || !isvchar(*(pc-1))) && (!*(pc+len) || !isvchar(*(pc+len))) ){
						while(pc3=strchr(pc2, '\t'))
							j++, pc2=pc3+1;
						i++;
						printf("%d. ��%d��, ��%d��\n", i, row, pc-pc1+1+j*7);
					}
					*pc++=c;
				}
				printf("���ҵ�%d�� \"%s\"\n", i, target);
			break;
			case 'X':
				system("cls");
			break;
			case 'Q':
				CtrlProc(0);
				return 0;
			break;
			default:
				printf(">>>switch case::This option was not found!\n");
		}
	}
}

void menu()
{
	printf("A.��������  B.�������  C.����  D.����ȫ��  E.��λ  F.ȫ�ʶ�λ  X.����  Q.�˳�\n��ѡ��: ");
}

char choose(char c)
{
	if(0x30<=c&&c<=0x39)
		c-=0x30;
	else if(0x41<=c&&c<=0x5a)
		c-=0x40;
	else if(0x61<=c&&c<=0x7a)
		c-=0x60;
	else
		c=-1;
	c+=0x40;
	printf(">>>��⵽ѡ��\'%c\'\n", c);
	return c;
}

BOOL WINAPI CtrlProc(DWORD dwCtrlType)
{
	switch(dwCtrlType)
	{
		case 0:
		case 1:
		case 2:
			fprintf(fp, "%s", buffer);
			fclose(fp);
			ShellExecute(NULL, "open", "notepad.exe", filepath, NULL, SW_SHOWNORMAL);
			free(filepath);
			free(buffer);
			free(target);
			return FALSE;
		default:
			return TRUE;
	}
}
