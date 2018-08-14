#include <__pink/pinkhat.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

unsigned char c;
char filename[256], filename1[265], _end[5]=".txt", x[64], buffer[193]={0}, *pc;
int len, i, j, k;
FILE *fp, *fp1;

unsigned char hexchar(unsigned char c);

int main(){
	double pus=pinkt();
loop:	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7|8);
	printf("请把要");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14|8);
	printf("解析");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7|8);
	printf("的文件拖到这里: ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11|8);
	scanf("%[^\n]%*c", filename);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7|8);
	if(filename[0]==34){
		filename[strlen(filename)-1]=0;
		strcpy(filename,filename+1);
	}
	strcpy(filename1,filename);
	if(pc=strrchr(filename1,'.'))
		*pc='_';
	strcat(filename1,_end);
	if(!(fp=fopen(filename,"rb"))){
		MessageBox(NULL,TEXT("打开文件失败！"),TEXT("Warining!"),MB_ICONWARNING);
		printf("Press Enter to exit ... ...\n");
		getchar();
		return 0;
	}
	if(!(fp1=fopen(filename1,"wb"))){
		MessageBox(NULL,TEXT("解析文件失败！"),TEXT("Warining!"),MB_ICONWARNING);
		printf("Press Enter to exit ... ...\n");
		getchar();
		return 0;
	}
	fseek(fp,0,SEEK_END);
	len=ftell(fp);
	rewind(fp);
	i=len/64;
	for(;i>0;i--){
		fread(x,4,16,fp);
		for(j=0;j<64;j++){
			c=x[j];
			pc=&buffer[(j+1)*3-1];
			*pc=0x20;
			for(k=1;k<=2;k++){
				*(pc-k)=hexchar(c%0x10);
				c>>=4;
			}
		}
		fprintf(fp1,"%s",buffer);
	}
	len%=64;
	for(;len>0;len--){
		fread(&c,1,1,fp);
		itoa(c,buffer,16);
		strupr(buffer);
		fprintf(fp1,"%02s ",buffer);
	}
	fclose(fp);
	fclose(fp1);
	i=MessageBox(NULL,TEXT("解析文件成功！是否继续解析文件?"),TEXT("Congratulations!"),MB_OKCANCEL);
	if(i==IDOK)
		goto loop;
	else{
		pause(1,pus,666666);
		return 0;
	}
}
unsigned char hexchar(unsigned char c)
{
	if(c<10)
		return c+0x30;
	else
		return c+0x37;
}
	