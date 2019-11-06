#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#include <sys/ioctl.h>
#include <termios.h>

#define SERVER_PORT 10213
#define MAX_LINE 256

void enable_raw_mode()
{
    termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON | ECHO); // Disable echo as well
    tcsetattr(0, TCSANOW, &term);
}

void disable_raw_mode()
{
    termios term;
    tcgetattr(0, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(0, TCSANOW, &term);
}

bool kbhit()
{
    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);
    return byteswaiting > 0;
}

int main(int argc,char * argv[])
{
	FILE *fp;
	struct hostent *hp;
	struct sockaddr_in sin;
	char *host;
	char buf[MAX_LINE];
	int s,flags;
	socklen_t len;

	host = "192.168.0.103";

	//Translate host name into peer's IP Address
	hp = gethostbyname(host);

	//build address data structure
	bzero((char *)&sin,sizeof(sin));
	sin.sin_family = AF_INET; //internet address
	bcopy(hp->h_addr,(char *)&sin.sin_addr,hp->h_length);
	sin.sin_port = htons(SERVER_PORT);
	
	//active open PF_INET is portocol family
	s = socket(PF_INET, SOCK_STREAM, 0);

	connect(s,(struct sockaddr *)&sin,sizeof(sin));


	//main loop: get and send lines of text
	while(1){
  	//while(fgets(buf,sizeof(buf),stdin)){
		enable_raw_mode();
		buf[MAX_LINE-1] = '\0';
		len = strlen(buf)+1;
		if(kbhit() == 'u'){
            buf[0] = 'u';
			send(s, buf, len, 0);
            sleep(.05);
		}else if(kbhit() == 'w'){
    	//}else if(buf[0] == 'w'){
      	    buf[0] = 'w';
			send(s, buf, len, 0);
            sleep(.05);
        }else if(kbhit() == 'a'){
		//}else if(buf[0] == 'a'){
            buf[0] = 'a';
			send(s, buf, len, 0);
            sleep(.05);
        }else if(kbhit() == 's'){
		//}else if(buf[0] == 's'){
            buf[0] = 's';
			send(s, buf, len, 0);
            sleep(.05);
        }else if(kbhit() == 'd'){
		//}else if(buf[0] == 'd'){
            buf[0] = 'd';
			send(s, buf, len, 0);
            sleep(.05);
        }else if(kbhit() == 'q'){
		//}else if(buf[0] == 'q'){
                buf[0] = 'q';
      		 	send(s, buf, len, 0);
                sleep(.05);
       			break;
		}
    	else{
    	}
        disable_raw_mode();
        tcflush(0,TCIFLUSH);
        sleep(.05);
	}
  	close(s);
}


