#ifndef _PHTTP_H_
#define _PHTTP_H_

#ifndef pPORT
#define pPORT 80
#endif

#define pWinHttpOpen(hSession) hSession = WinHttpOpen(L"User Agent", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

#define pWinHttpConnect(hConnect, hSession, domain_ip) hConnect = WinHttpConnect(hSession, domain_ip, pPORT, 0);

#define pWinHttpOpenRequest(hRequest, hConnect, _url_file)\
		hRequest = WinHttpOpenRequest(hConnect, L"POST", _url_file, L"HTTP/1.1", WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);

#define pWinHttpSendRequest(hRequest) WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);

#define pWinHttpReceiveResponse(hRequest) WinHttpReceiveResponse(hRequest,NULL);

#define pWinHttpLoopRead_P(hRequest, fp){\
		DWORD dwSize, dwDownloaded;\
		char* szOutBuffer=new char[32];\
		do{\
			dwSize=0;\
			WinHttpQueryDataAvailable(hRequest, &dwSize);\
			if(!dwSize)\
				break;\
			if(sizeof(szOutBuffer)<dwSize){\
				delete[] szOutBuffer;\
				szOutBuffer=new char[dwSize+1];\
				if(!szOutBuffer)\
					break;\
			}\
			memset(szOutBuffer,0,dwSize+1);\
			WinHttpReadData(hRequest, (LPVOID)szOutBuffer, dwSize, &dwDownloaded);\
			fwrite(szOutBuffer, dwDownloaded, 1, fp);\
			if(!dwDownloaded)\
				break;\
		}while(dwSize>0);\
		delete[] szOutBuffer;\
	}

#define pWinHttpLoopRead_C(hRequest, fp){\
		DWORD dwSize, dwDownloaded;\
		char* szOutBuffer=(char*)malloc(32);\
		if(szOutBuffer)\
			memset(szOutBuffer,0,32);\
		do{\
			dwSize=0;\
			WinHttpQueryDataAvailable(hRequest, &dwSize);\
			if(!dwSize)\
				break;\
			if(sizeof(szOutBuffer)<dwSize){\
				free(szOutBuffer);\
				szOutBuffer=(char*)malloc(dwSize+1);\
				if(!szOutBuffer)\
					break;\
			}\
			memset(szOutBuffer,0,dwSize+1);\
			WinHttpReadData(hRequest, (LPVOID)szOutBuffer, dwSize, &dwDownloaded);\
			fwrite(szOutBuffer, dwDownloaded, 1, fp);\
			if(!dwDownloaded)\
				break;\
		}while(dwSize>0);\
		free(szOutBuffer);\
	}

#ifdef __cplusplus
#define pWinHttpLoopRead(hRequest, fp) pWinHttpLoopRead_P(hRequest, fp)
#else
#define pWinHttpLoopRead(hRequest, fp) pWinHttpLoopRead_C(hRequest, fp)
#endif

#define pWinhttpCloseHandle(hSession, hConnect, hRequest)\
		hRequest && WinHttpCloseHandle(hRequest);\
		hConnect && WinHttpCloseHandle(hConnect);\
		hSession && WinHttpCloseHandle(hSession);

DWORD pDownload(wchar_t* domain_ip, wchar_t* _file_url, char* localfilepath)
{
	FILE* fp;
	HINTERNET hSession, hConnect, hRequest;
	pWinHttpOpen(hSession);
		__ReturnError();
	pWinHttpConnect(hConnect, hSession, domain_ip);
		__ReturnError();
	pWinHttpOpenRequest(hRequest, hConnect, _file_url);
		__ReturnError();
	pWinHttpSendRequest(hRequest);
		__ReturnError();
	pWinHttpReceiveResponse(hRequest);
		__ReturnError();
	fp=fopen(localfilepath, "wb");
	pWinHttpLoopRead(hRequest, fp);
	int ret=GetLastError();
	fclose(fp);
	pWinhttpCloseHandle(hSession, hConnect, hRequest);
	return ret;
}





















#undef PORT

#endif