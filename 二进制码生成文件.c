#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

unsigned char c;
char filename[256], filename1[265], x[64], buffer[577]={0}, *pc;
int len, i, j, k;
FILE *fp, *fp1;

int main(){
loop:	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7|8);
	printf("请把要");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14|8);
	printf("生成文件");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7|8);
	printf("的源码文件拖到这里: ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11|8);
	scanf("%[^\n]%*c", filename);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7|8);
	if(filename[0]==34){
		filename[strlen(filename)-1]=0;
		strcpy(filename,filename+1);
	}
	strcpy(filename1,filename);
	if(pc=strrchr(filename1,'_'))
		*pc='.';
	if(pc=strrchr(filename1,'.'))
		*pc=0;
	if(!(fp=fopen(filename,"rb"))){
		MessageBox(NULL,TEXT("打开文件失败！"),TEXT("Warining!"),MB_ICONWARNING);
		printf("Press Enter to exit ... ...\n");
		getchar();
		return 0;
	}
	if(!(fp1=fopen(filename1,"wb"))){
		MessageBox(NULL,TEXT("生成文件失败！"),TEXT("Warining!"),MB_ICONWARNING);
		printf("Press Enter to exit ... ...\n");
		getchar();
		return 0;
	}
	fseek(fp,0,SEEK_END);
	len=ftell(fp);
	rewind(fp);
	len/=9;
	i=len/64;
	for(;i>0;i--){
		fread(buffer,8,72,fp);
		for(j=0;j<64;j++){
			c=0;
			pc=&buffer[j*9];
			for(k=0;k<7;k++){
				c+=(*(pc+k)-0x30);
				c<<=1;
			}
			c+=(*(pc+k)-0x30);
			x[j]=c;
		}
		fwrite(x,4,16,fp1);
	}
	len%=64;
	for(;len>0;len--){
		fread(buffer,1,9,fp);
		c=0;
		for(i=0;i<7;i++){
			c+=(buffer[i]-0x30);
			c<<=1;
		}
		c+=(buffer[i]-0x30);
		fwrite(&c,1,1,fp1);
	}
	fclose(fp);
	fclose(fp1);
	i=MessageBox(NULL,TEXT("生成文件成功！是否继续生成文件?"),TEXT("Congratulations!"),MB_OKCANCEL);
	if(i==IDOK)
		goto loop;
	else
		return 0;
}