#ifndef LINUX
	#define WINDOWS
#endif
#ifdef WINDOWS
	#include <winsock2.h>
	#include <ws2tcpip.h>
#endif
#ifdef LINUX
	
#endif

#define RECV_STILL		0
#define RECV_SUCCEED	1
#define RECV_FAILED		-1

class NETWORK{
private:
	SOCKET Socket;	//送受信・サーバー側ソケット
	sockaddr_in ServerAddr;	//サーバ側アドレス
public:
	NETWORK();
	~NETWORK();
	//server func
	void Listen(u_short port);
	bool Accept(SOCKET *soc, sockaddr_in *addr);
	int Recv(SOCKET soc, char *pData, int DataSize, int *pRecvSize);
	bool Send(SOCKET soc, char *pData, int DataSize);
	void Close(SOCKET soc);
	//client func
	bool Connect(const char *ip, u_short port);
	int Recv(char *pData, int DataSize, int *pRecvSize);
	bool Send(char* pData, int DataSize);
};

