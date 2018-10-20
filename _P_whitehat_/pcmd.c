#include <stdio.h>
#include <windows.h>
//#include <winhttp.h>
#include <unistd.h>
#include <string.h>
#include <__pink/pinkwin.h>
//#include <__pink/phttp.h>

#ifndef __PINK__
#define __PINK__ 	-0x50494E4BL
#endif

int dofunc();
int create_wh();

int main(){
	int ret=dofunc();
	if( ret!=0 )
		printf("Error::ret=%d\n", ret);
	return 0;
}

int dofunc()
{
	FILE* fp;
	int flag;
	if(access(".wh", F_OK))
		create_wh();
	else{
		fp=fopen(".wh", "rb+");
		if(!fp)
			return -10;
		if( fread(&flag, 4, 1, fp)!=1 )
			return -11;
		if(flag!=__PINK__){
			fclose(fp);
			create_wh();
			return -12;
		}
	}
	return 0;
}

int create_wh()
{
	FILE* fp;
	fp=fopen(".wh", "wb");
	if(!fp)
		return -1;
	int flag=__PINK__;
	if( fwrite(&flag, 4, 1, fp)!=1 ){
		fclose(fp);
		return -2;
	}
	return 0;
}