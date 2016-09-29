#include <iostream>
#include "Network.h"
using namespace std;

#define PORT		10000
#define MAX_PACKET	1024

int main(int argc, char *argv[]){
	NETWORK net;
	SOCKET soc = INVALID_SOCKET;
	sockaddr_in	addr;
	int recvsize;
	char data[MAX_PACKET];
	
	net.Listen(PORT);
	cout<<"サーバ待ち受け状態です。"<<endl<<"クライアントを起動してください"<<endl;
	
	while(true){
		if(soc==INVALID_SOCKET && net.Accept(&soc, &addr)){
			cout<<"accept "<<inet_ntoa(addr.sin_addr)<<" sock = "<<soc<<endl;
		}
		
		int status = net.Recv(soc, data, sizeof(data), &recvsize);
		if(status == RECV_SUCCEED){
			cout<<"socket="<<soc<<" recvsize="<<recvsize<<" data: "<<data<<endl;
		}else if(status == RECV_FAILED){
		//	cout<<"recv failed."<<endl;
		}
		
		
	/*	if(soc != INVALID_SOCKET){
			string str;
			cout<<"input : ";
			cin>>str;
			cout<<"sending \""<<str<<"\""<<endl;
			net.Send(soc, (char*)str.c_str(), sizeof(str.c_str()));
		}
	*/
	}
	
	return 0;
}

