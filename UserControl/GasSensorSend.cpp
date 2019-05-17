//Gas Sensor Sender on Linux
//compile code g++ -o gss GasSensorSend.cpp -lwiringPi -lrt -lm -lcrypt -lpthread
#include <stdio.h>
#include <wiringPi.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string>
#include <iostream>
#include <bits/stdc++.h>

#define ADC_port 1 //pin #37, XADC0AIN_0
#define SERVER_PORT 10500

int main(int argc, char *argv[])
{
	int analogVal;
	FILE *fp;
	struct hostent *hp;
	struct sockaddr_in sin;
	char *host;
	char buf[256];
	int s, len;
    int n;
    char hold[256];

	if(argc == 2)
		host = argv[1];
	else{
		fprintf(stderr,"Invalid host");
		exit(1);
	}
	
	hp = gethostbyname(host);
	if(hp == NULL){
		herror("gethostbyname");
		exit(1);
	}
	
	bzero((char *)&sin,sizeof(sin));
	sin.sin_family = AF_INET; //internet address
	bcopy(hp->h_addr,(char *)&sin.sin_addr,hp->h_length);
	sin.sin_port = htons(SERVER_PORT);

	
	if((s = socket(PF_INET, SOCK_STREAM, 0))<0){
		perror("socket");
		exit(1);
	}
	
	if(connect(s,(struct sockaddr *)&sin,sizeof(sin)) < 0){
		perror("connect");
		close(s);
		exit(1);
	}
	
	if(wiringPiSetup() == -1){
		printf("setup wiringPi failed!\n");
		return 1;
	}
	while(1){
		analogVal = analogRead(ADC_port);
        std::string str = std::to_string(analogVal);
        n = str.length();
        strcpy(buf,str.c_str());
        //printf("buffer %s\n" ,buf);
        buf[255]='\0';
        len = strlen(buf)+1;
		send(s, buf, len, 0);
		delay(500);
	}
	return 0;
}
