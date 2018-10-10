//#include <stdio.h>
#include <iostream>
#include <winsock2.h>
#include <__pink/pinkwin.h>
#include <__pink/psocket.h>
#include <__pink/pinkcli.h>

int PORT=44000;
char IP_ADDRESS_DFT[]="192.168.1.103";
char* IP_ADDRESS=IP_ADDRESS_DFT;

int mrecv=0, msend=0;

int WINAPI RecvThread(SOCKET* skt)
{
	SOCKET ServerSocket=*skt;
	char RecvBuffer[1024];
	memset(RecvBuffer, 0, sizeof(RecvBuffer));
	while( recv(ServerSocket,RecvBuffer,sizeof(RecvBuffer),0)>0 ){
		pColor(c);
		printf("云端消息~%d: ", ++mrecv);
		pColor(f);
		printf("\"%s\"\n", RecvBuffer);
		pColor(b);
		memset(RecvBuffer, 0, sizeof(RecvBuffer));
	}
	pColor(4);
	printf("与服务器的连接断开\n");
	pColor(f);
	return 0;
}

int main(int argc, char** argv){
	char* rchr;
	if(argc>1){
		IP_ADDRESS=*(argv+1);
		if( rchr=strrchr(*(argv+1), ':') ){
			*rchr++=0;
			PORT=atoi((const char*)rchr);
		}
	}
	pColorInit();
	WSADATA Ws;
	SOCKET ServerSocket;
	struct sockaddr_in ServerAddr, LocalAddr;
	char SendBuffer[1024];
	HANDLE hThread=NULL;
	WSAStartup(MAKEWORD(2,2), &Ws);
		__ReportError(NULL,0,0x0f00);
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		__ReportError(NULL,0,0x0f10);
	pSINinit(ServerAddr, IP_ADDRESS, PORT);
	pconnect(ServerSocket, ServerAddr);
		__ReportError(NULL,0,0x0f20);
	hThread=pCreateThread(RecvThread, &ServerSocket);
		__ReportError(NULL,0,0x0f80);
	pColor(e);
	printf("<连接成功> 现在可以通信:\n");

	while(1){
		pColor(b);
//		scanf("%1024[^\n]%*c", SendBuffer);
		do{
			std::cin.getline(SendBuffer, sizeof(SendBuffer));
		}while(strlen(SendBuffer)<=0);
		if(send(ServerSocket, SendBuffer, (int)strlen(SendBuffer), 0)==SOCKET_ERROR)
			break;
		else{
			pColor(a);
			printf("发送成功~%d\n", ++msend);
		}
	}
	CloseHandle(hThread);
	closesocket(ServerSocket);
	closesocket(ServerSocket);
	WSACleanup();
	return 0;
}