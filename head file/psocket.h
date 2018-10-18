#ifndef _PSOCKET_H_
#define _PSOCKET_H_

#define pStart(){\
		WSADATA Ws;\
		WSAStartup(MAKEWORD(2,2), &Ws);\
	}

#define psocket(x) x=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)

#define pSINinit(sin, ip_addr, port){\
		sin.sin_family=AF_INET;\
		sin.sin_addr.s_addr=inet_addr(ip_addr);\
		sin.sin_port=htons(port);\
		*(long long*)sin.sin_zero=0;\
	}

#define pconnect(OneSocket, OneAddr) connect(OneSocket,(struct sockaddr*)&OneAddr, sizeof(OneAddr))

#define pbind(OneSocket, OneAddr) bind(OneSocket,(struct sockaddr*)&OneAddr, sizeof(OneAddr))

#define paccept(AcceptSocket, OneSocket, OneAddr){\
		int AddrLen=sizeof(OneAddr);\
		AcceptSocket=accept(OneSocket, (struct sockaddr*)&OneAddr, &AddrLen);\
	}

#define pCreateThread(ThreadProc, param) CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, param, 0, NULL)

















#endif