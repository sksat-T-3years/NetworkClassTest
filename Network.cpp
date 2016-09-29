#include "Network.h"

NETWORK::NETWORK(){
	Socket = INVALID_SOCKET;
#ifdef WINDOWS
	WSADATA data;
	WSAStartup(MAKEWORD(2,0), &data);
#endif //WINDOWS
}

NETWORK::~NETWORK(){
	if(Socket != INVALID_SOCKET)
		closesocket(Socket);
#ifdef WINDOWS
	WSACleanup();
#endif //WINDOWS
}

void NETWORK::Listen(u_short port){
	memset(&ServerAddr, 0, sizeof(ServerAddr));
	ServerAddr.sin_port			= htons(port);
	ServerAddr.sin_family		= AF_INET;
	ServerAddr.sin_addr.s_addr	= htonl(INADDR_ANY);
	
	Socket = socket(AF_INET, SOCK_STREAM, 0);
	
	bind(Socket, (sockaddr*)&ServerAddr, sizeof(ServerAddr));
	
	listen(Socket, 5);
	
	//ノンブロッキングに設定
	u_long val = 1;
	ioctlsocket(Socket, FIONBIO, &val);
	
	return;
}

bool NETWORK::Accept(SOCKET *soc, sockaddr_in *addr){
	int AddrSize = sizeof(sockaddr_in);
	*soc = accept(Socket, (sockaddr*)addr, &AddrSize);
	if(*soc != INVALID_SOCKET){
		//接続ソケットを非同期モードに
		u_long val = 1;
		ioctlsocket(*soc, FIONBIO, &val);
		return true;
	}
	
	return false;
}

int NETWORK::Recv(SOCKET soc, char *pData, int DataSize, int *pRecvSize){
	int n = recv(soc, pData, DataSize, 0);
	if(n < 1){
		if(WSAGetLastError() == WSAEWOULDBLOCK){
			return RECV_STILL;
		}else{
			return RECV_FAILED;
		}
	}
	*pRecvSize = n;
	return RECV_SUCCEED;
}

bool NETWORK::Send(SOCKET soc, char *pData, int DataSize){
	if(send(soc, pData, DataSize, 0) == SOCKET_ERROR)
		return false;
	
	return true;
}

void NETWORK::Close(SOCKET soc){
	closesocket(soc);
}


//client func
bool NETWORK::Connect(const char *ip, u_short port){
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_port			= htons(port);
	addr.sin_family			= AF_INET;
	addr.sin_addr.s_addr	= inet_addr(ip);
	
	Socket = socket(AF_INET, SOCK_STREAM, 0);
	
	if(connect(Socket, (const sockaddr*)(&addr), sizeof(addr)) == SOCKET_ERROR)
		return false;
	
	//非同期モード
	u_long val = 1;
	ioctlsocket(Socket, FIONBIO, &val);
	return true;
}

int NETWORK::Recv(char *pData, int DataSize, int *pRecvSize){
	int n = recv(Socket, pData, DataSize, 0);
	
	if(n < 1){
		if(WSAGetLastError() == WSAEWOULDBLOCK){
			//データが来ていない
			return RECV_STILL;
		}else{
			//切断かエラー
			return RECV_FAILED;
		}
	}
	
	*pRecvSize = n;
	return RECV_SUCCEED;
}

bool NETWORK::Send(char* pData, int DataSize){
	if(send(Socket, pData, DataSize, 0) == SOCKET_ERROR)
		return false;
	
	return true;
}

