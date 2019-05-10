#include <iostream>
#include <winsock2.h>
#include <stdio.h>
 
using namespace std;
 
int main()
{
    WSADATA WSAData;
 
    SOCKET server, client;
	int len;
    SOCKADDR_IN serverAddr, clientAddr;
 
    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);
 
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(10500);
 
    bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
    listen(server, 0);
 
    cout << "Listening for incoming connections..." << endl;
	
    char buf[256];
    int clientAddrSize = sizeof(clientAddr);
	while(1){
			if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize))!= INVALID_SOCKET){
					cout << "Client connected!" << endl;
					while(recv(client,buf,sizeof(buf),0)){
						//recv(client,buf,sizeof(buf),0);
						printf("Gas Sensor Reads: %s\n",buf);
						memset(buf,0,sizeof(buf));
					}
				}
	}
	closesocket(client);
	cout << "Client DC." << endl;
}