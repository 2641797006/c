#include <stdio.h>
#include <windows.h>
//#include <winhttp.h>
#include <unistd.h>
#include <string.h>
#include <__pink/pinkwin.h>
#include <__pink/pfile.h>
#include <__pink/pstruct.h>
//#include <__pink/phttp.h>

#ifndef __PINK__
#define __PINK__	-0x50494E4BL
#endif

void pset_wh(_WH* _wh);
int dofunc(char* filepath);

int main(){
	char *fileindex=getenv("PUBLIC"), *GlobalBuffer=(char*)malloc(1024), *filepath=GlobalBuffer;
	char *dir[2]={"/_P_WhiteHat_", "/.wh"};
	if(!GlobalBuffer)
		return -1;
	pmkdir(filepath, fileindex, dir, 1);
	strcat(filepath, dir[1]);
	dofunc(filepath);
	return 0;
}

int dofunc(char* filepath)
{
	FILE* fp;
	_WH _wh;
	pset_wh(&_wh);
	if(access(filepath, F_OK))
		pfile_wb(filepath, &_wh, 96);
	else{
		fp=fopen(filepath, "rb+");
		if(!fp)
			return -1;
		if( fread(&_wh, 96, 1, fp)!=1 )
			_wh.flag=-1;
		if(_wh.flag!=__PINK__){
			fclose(fp);
			pset_wh(&_wh);
			pfile_wb(filepath, &_wh, 96);
			return -2;
		}
	}
	return 0;
}

void pset_wh(_WH* _wh)
{
	_wh->flag=__PINK__;
	_wh->version=101;
	strcpy(_wh->word, "\r\nThis file is use for pcmd.exe!\r\nversion : 1.01\r\n");
}