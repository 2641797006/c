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
HANDLE hThread=NULL, hThread2=NULL;

int WINAPI RecvThread(SOCKET* skt)
{
	SOCKET ClientSocket=*skt;
	char RecvBuffer[1024];
	memset(RecvBuffer, 0, sizeof(RecvBuffer));
	while( recv(ClientSocket,RecvBuffer,sizeof(RecvBuffer),0)>0 ){
		pColor(e);
		printf("客户消息~%d: ", ++mrecv);
		pColor(f);
		printf("\"%s\"\n", RecvBuffer);
		pColor(b);
		memset(RecvBuffer, 0, sizeof(RecvBuffer));
	}
	pColor(4);
	printf("与客户端的连接断开\n");
	pColor(b);
	return 0;
}

int WINAPI SendThread(SOCKET* skt)
{
	SOCKET ClientSocket=*skt;
	char SendBuffer[1024];
	while(1){
		pColor(b);
//		scanf("%1024[^\n]%*c", SendBuffer);
		do{
			std::cin.getline(SendBuffer, sizeof(SendBuffer));
		}while(strlen(SendBuffer)<=0);
		if(send(ClientSocket, SendBuffer, (int)strlen(SendBuffer), 0)==SOCKET_ERROR)
			break;
		else{
			pColor(a);
			printf("发送成功~%d\n", ++msend);
		}
	}
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
	SOCKET LocalSocket, ClientSocket;
	struct sockaddr_in LocalAddr, ClientAddr;
	WSAStartup(MAKEWORD(2,2), &Ws);
		__ReportError(NULL,0,0x0f00);
	LocalSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		__ReportError(NULL,0,0x0f10);
	pSINinit(LocalAddr, IP_ADDRESS, PORT);
	pbind(LocalSocket, LocalAddr);
		__ReportError(NULL,0,0x0f11);
	listen(LocalSocket, 10);
		__ReportError(NULL,0,0x0f12);
	pColor(e);
	printf("服务端已启动\n");
	while(1){
		paccept(ClientSocket, LocalSocket, ClientAddr);
			__ReportError(NULL,0,0x0f20);
		pColor(c);
		printf("客户端连接: %s:%d\n", inet_ntoa(ClientAddr.sin_addr), ClientAddr.sin_port);
		hThread=pCreateThread(RecvThread, &ClientSocket);
			__ReportError(NULL,0,0x0f30);
		hThread2=pCreateThread(SendThread, &ClientSocket);
			__ReportError(NULL,0,0x0f50);
		CloseHandle(hThread);
		CloseHandle(hThread2);
	}
	closesocket(LocalSocket);
	closesocket(ClientSocket);
	WSACleanup();
	return 0;
}