//GasSensorRecv.cpp
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

#define SERVER_PORT 10502

int main(intargc, char *argv[])
{
    struct sockaddr_in sin;
    char buf[256];
    socklen_t len;
    int s, new_s;

    bzero((char *)&sin,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);

    s = socket(PF_INET,SOCK_STREAM,0);
    bind(s, (struct sockaddr *)&sin, sizeof(sin));
    listen(s, MAX_PENDING);
    
    while(1){
        new_s = accept(s, (struct sockaddr *)&sin, &len);
        while(recv(new_s, buf, len, 0) != 0)
        {
            printf("Gas Sensor Reads: %s\n",buf);
        }
        close(new_s);
        close(s);
        return 0;    
    }
    
}
