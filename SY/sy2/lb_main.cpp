#include <iostream>
#include <windows.h>
using std::cin;
using std::cout;
using std::endl;

#define ResetCin() ( cin.clear(), cin.sync() )

#define DWORD unsigned long
class GUN{
	public:
		char name[16];
		DWORD Damage;
		DWORD Range;
		DWORD FiringRate;
		DWORD MagSize;
};

#define ElemType GUN
#include <C:/Users/26417/Desktop/CPP/LNode/LNode.h>
using namespace ppLNode;

LNode* L;
char GlobalBuffer[0x100];

void menu();
char choose(char c);
void PrintElem(ElemType* e);
void ScanElem(ElemType* e);

int main()
{
	//std::ios::sync_with_stdio(false);
	*GlobalBuffer='?';

	char c;
	int i;
	GUN gun;
	sprintf(gun.name, "%s", "AWM");
	gun.Damage=120;
	gun.Range=1200;
	gun.FiringRate=2;
	gun.MagSize=5;
	L=new LNode;
	L->Insert(1,&gun);

	while(1)
	{
		menu();
		cin.getline(GlobalBuffer+1, 0xff);
		ResetCin();
		if( sscanf(GlobalBuffer, "%*[^0-9a-zA-Z]%1[0-9a-zA-Z]", &c)<1 )
			continue;
		c=choose(c);
		switch(c)
		{
			case 'A':
				if(L->Length()<1)
					cout<<"暂时没有数据."<<endl;
				else
					L->Print(&PrintElem);
			break;
			case 'B':
				cout<<"请输入第"<<L->Length()+1<<"个数据."<<endl;
				ScanElem(&gun);
				L->Insert(L->Length()+1, &gun);
			break;
			case 'C':
				L->Destroy();
				delete L;
				L=new LNode;
				cout<<"数据已清空\n";
			break;
			case 'D':
				if(L->Length()<1){
					cout<<"暂时没有数据\n";
					break;
				}
				cout<<"请输入要删除数据的序号: ";
				i=-1;
				cin>>i;
				ResetCin();
				if(i<1||!L->Delete(i)&&!_PPLNODE_)
					cout<<"没有删除数据\n";
				else
					cout<<"已删除第\""<<i<<"\"个数据\n";
			break;
			case 'E':
				if(L->Length()<1){
					cout<<"暂时没有数据\n";
					break;
				}
				cout<<"请输入待修改数据的序号: ";
				i=-1;
				cin>>i;
				ResetCin();
				if(i<1||i>L->Length()){
					cout<<"位置错误\n";
					break;
				}
				cout<<"请输入新数据:\n";
				ScanElem(&gun);
				CopyElem( &L->GetElem(i)->data, &gun);
				cout<<"已修改第\""<<i<<"个数据\n";
			break;
			case 'K':
				ShellExecute(NULL, "open", "https://2641797006.github.io/html/datasSY/SY2.html", NULL, NULL, SW_SHOWNORMAL);
			break;
			case 'Q':
				return 0;
			break;
			case 'X':
				system("cls");
			break;
			default:
				cout<<">>>switch case::This option was not found!\n";
		}
	}
}

void menu()
{
	cout<<"\nA.输出  B.输入  C.清空  D.删除  E.修改  X.清屏  K.开源  Q.退出\n请选择: ";
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
	printf(">>>检测到选项\'%c\'\n\n", c);
	return c;
}

void PrintElem(ElemType* e)
{
	cout<<"GUN:  "<<e->name<<endl
	<<"伤害: "<<e->Damage<<endl
	<<"射程: "<<e->Range<<"m"<<endl
	<<"射速: "<<e->FiringRate<<endl
	<<"弹容: "<<e->MagSize<<endl<<endl;
}

void ScanElem(ElemType* e)
{
	cout<<"枪械名称: ";
	cin.get(e->name, 16, '\n');
	ResetCin();
	cout<<"伤害: ";
	cin>>e->Damage;
	ResetCin();
	cout<<"射程: ";
	cin>>e->Range;
	ResetCin();
	cout<<"射速: ";
	cin>>e->FiringRate;
	ResetCin();
	cout<<"弹容: ";
	cin>>e->MagSize;
	ResetCin();
}