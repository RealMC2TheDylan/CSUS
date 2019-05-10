//Windows User Control Sender
#include <iostream>
#include <winsock2.h>
#include <conio.h>
 
using namespace std;
 
int main()
{
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;
	int key;
	int len;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);
	
	addr.sin_addr.s_addr = inet_addr("192.168.0.102");
    //addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // replace the ip with your futur server ip address. If server AND client are running on the same computer, you can use the local ip 127.0.0.1
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5559);
 
    connect(server, (SOCKADDR *)&addr, sizeof(addr));
    cout << "Connected to server!" << endl;
	char buffer[25];
	while(1){
		//char buffer[1024]={'h', 'e', 'l', 'l', 'o', '.'};
		if(_kbhit()){
			key = getch();
			buffer[24] = '\0';
			len = strlen(buffer)+1;
			if (key == 'u'){
				buffer[0] = 'u';
				send(server, buffer, sizeof(buffer), 0);
			}else if(key == 'w'){
				buffer[0] = 'w';
				send(server,buffer,sizeof(buffer),0);
			}else if(key == 'a'){
				buffer[0] = 'a';
				send(server,buffer,sizeof(buffer),0);
			}else if(key == 's'){
				buffer[0] = 's';
				send(server,buffer,sizeof(buffer),0);
			}else if(key == 'd'){
				buffer[0] = 'd';
				send(server,buffer,sizeof(buffer),0);
			}else{
			}
			if(key == 'q'){
				buffer[0] = 'q';
				send(server,buffer,len,0);
				break;
			}
			Sleep(.2);
			cout << "Message sent!" << endl;
		}
	}
	closesocket(server);
	WSACleanup();
	cout << "Socket closed." << endl << endl;
}