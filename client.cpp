#include <iostream>
#include <iomanip>	//std::setw(int)
#include <string>
#include "Network.h"
using namespace std;

#define ServerIP	"127.0.0.1"
#define PORT		10000
#define MAX_PACKET	1024

int main(int argc, char *argv[]){
	NETWORK net;
	int recvsize;
	char *data = new char[MAX_PACKET];
	
start:
	
	if(!net.Connect(ServerIP, PORT)){
		cout<<"connect failed."<<endl;
		goto start;
	}else{
		cout<<"connect."<<endl;
	}
	
	while(true){
		int status = net.Recv(data, sizeof(data), &recvsize);
		if(status == RECV_SUCCEED){
			cout<<"recv"<<endl;
		}else if(status == RECV_FAILED){
			cout<<"サーバから切断されました。"<<endl;
			break;
		}else{
			cout<<"client$ ";
			cin>>setw(MAX_PACKET)>>data;
			net.Send(data, MAX_PACKET);
		}
	}
	
	return 0;
}

