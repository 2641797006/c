#include <stdio.h>
#include <windows.h>
#include <winhttp.h>
#include <string.h>
#include <__pink/pinkwin.h>
#include <__pink/phttp.h>

int main(int argc, char** argv){
	if(argc<2){
		printf("error: domain/ip=?.?.?.?\n");
		return -1;
	}
	else if(argc<3){
		printf("error: _url_file=???\n");
		return -1;
	}
	else if(argc<4){
		printf("error: local file path miss\n");
		return -1;
	}
	FILE* fp;
	wchar_t domain_ip[256], _url_file[512];
	HINTERNET hSession=NULL, hConnect=NULL, hRequest=NULL;
	pAtoW(*(argv+1),domain_ip,256);
	pAtoW(*(argv+2),_url_file,512);
	pWinHttpOpen(hSession);
		__ReportError(NULL,0,0x0f00);
	pWinHttpConnect(hConnect, hSession, domain_ip);
		__ReportError(NULL,0,0x0f10);
	pWinHttpOpenRequest(hRequest, hConnect, _url_file);
		__ReportError(NULL,0,0x0f20);
	pWinHttpSendRequest(hRequest);
		__ReportError(NULL,0,0x0f30);
	pWinHttpReceiveResponse(hRequest);
		__ReportError(NULL,0,0x0f40);

	fp=fopen(*(argv+3), "wb");
	pWinHttpLoopRead(hRequest, fp);
		__ReportError(NULL,0,0x0f50);
	fclose(fp);

	pWinhttpCloseHandle(hSession, hConnect, hRequest);

	return 0;
}