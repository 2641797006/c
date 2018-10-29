#include <stdio.h>
#include <__pink/pfile.h>
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

void menu();
int choose(int n);
void printelem(ElemType* pe);
int scanfelem(ElemType* pe, int i);
void stuave(ElemType* pe);
void format_wh(_WH* _wh);

int main()
{
	int i;
	SqList L;
	STUDENT student;
	InitList(&L);

	_WH _wh;
	FILE* fp;
	char *penv=getenv("PUBLIC"), *filepath=(char*)malloc(1024), *filepath_bak=(char*)malloc(1024);
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
	else
		while( fread(&student, sizeof(STUDENT), 1, fp)==1 )
			ListInsert(&L, L.length+1, &student);
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
					printf("���Ա���û������\n");
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
				printf("���Ա������\n");
			break;
			case 'D':
				if(L.length==0){
					printf("���Ա���û������\n");
					break;
				}
				printf("������Ҫɾ����Ԫ��λ��: ");
				scanf("%*[^0-9]%d%*[^\n]", &i);
				if( ListDelete(&L, i, NULL) )
					printf("λ�ô���: %d\n", i);
				else
					printf("��ɾ����%d��ѧ����Ϣ\n", i);
			break;
			case 'E':
				if(L.length==0){
					printf("���Ա���û������\n");
					break;
				}
				printf("������Ҫ�޸�ѧ����Ϣ�����: ");
				scanf("%*[^0-9]%d%*[^\n]", &i);
				if( i<1||i>L.length )
					printf("��Ŵ���\n");
				else{
					scanfelem(&student, i);
					CopyElem(L.elem+i-1, &student);
					printf("���޸ĵ�%d��ѧ������Ϣ\n", i);
				}
			break;
			case 'K':
				system("cls");
			break;
			case 'Q':
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
				return 0;
			}
			break;
			case 'U':
			{
				int num=0;
				ElemType *pe=L.elem, *end=L.elem+L.length-1;
				printf(">>>��60������ѧ�Ƶ�ѧ��:\n");
				while(pe<=end){
					for(i=0;i<4;i++)
						if(pe->grade[i]<60){
							num++;
							printelem(pe);
							break;
						}
					pe++;
				}
				printf(">>>��%d��\n", num);
			}
			break;
			case 'V':
			{
				int num=0;
				ElemType *pe=L.elem, *end=L.elem+L.length-1;
				printf(">>>��90������ѧ�Ƶ�ѧ��:\n");
				while(pe<=end){
					for(i=0;i<4;i++)
						if(pe->grade[i]>=90){
							num++;
							printelem(pe);
							break;
						}
					pe++;
				}
				printf(">>>��%d��\n", num);
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
	printf("\nA.���  B.����  C.���  D.ɾ��  E.�޸�  K.����  U.60������  V.90������  Q.�˳�\n��ѡ��: ");
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
	printf(">>>��⵽ѡ��\'%c\'\n\n", n);
	return n;
}

void printelem(ElemType* pe)
{
	printf("����: %s \nѧ��: %s \n�ɼ�: %-5.3G %-5.3G %-5.3G %-5.3G \nƽ����: %.6G\n\n",
		pe->name, pe->ID, pe->grade[0], pe->grade[1], pe->grade[2], pe->grade[3], pe->average);
}

int scanfelem(ElemType* pe, int i)
{
	printf("�������%d��ѧ��������. \n>>>����: ", i);
	scanf("%*c%15[^\n]%*[^\n]", pe->name);
	printf(">>>ѧ��: ");
	scanf("%*[^0-9a-zA-Z]%15[0-9a-zA-Z]%*[^\n]", pe->ID);
	printf(">>>�ĿƳɼ�: ");
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






