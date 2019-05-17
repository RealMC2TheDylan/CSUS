// Motor code integrated with Control program to receive commands through TCP private network on Linux
//compile code g++ -o cr -lwiringPi -lrt -lm -lcrypt -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <wiringSerial.h>
#include <wiringPi.h>
#include <cmath>

const int fd = serialOpen("/dev/ttySAC0",38400);
const int tickmax = 60;

int constrain(int power, int low, int high){
    if(power > high){
        power = high;    
    }else if(power < low){
        power = low;    
    }else
        return power;
}

void motordrive(int motor,int power){
    char command;
    power = constrain(power,-63,63);
    
    if(motor == 1){
        command = 64 + power;
    }else if(motor == 2){
        command = 191 + power;
    }
    printf("power %i", command);
    serialPuts(fd, &command);
    serialPuts(fd, &command);
}

void motorcontrol(char c, int tickcnt){
    int motor,pr,pl,loop;
    double ul, ur;
    double L, vx,vz,r;
     
    L = .420;
    r = .1275;
    motordrive(1, 0);
    motordrive(2, 0);
    while(1){

        if(c == 'w' && tickcnt != tickmax){
            //printf("%d\n",tickcnt);
            vz = 0;
            vx = .6;
            ul = (-.5*vz*L+vx)/r;
            ur = (.5*vz*L+vx)/r;    
            
            if(vx > 0){
                pr = round((ur / .1937));
                pl = round((ul / .1937));        
            }else if(vx < 0){
                pr = round((ur / .1934));
                pl = round((ul / .1934));
            }else{
                pr = 0;
                pl = 0;
            }
            motordrive(1,pr);
            motordrive(2,pl);        
            tickcnt++;
            //delay(50);

        }else if(c == 'a' && tickcnt != tickmax){
            vz = 1.5;
            vx = 0;
            ul = (-.5*vz*L+vx)/r;
            ur = (.5*vz*L+vx)/r;    
            
            //if(vx > 0){
                pr = round((ur / .1937));
                pl = round((ul / .1937));        
            /*}else if(vx < 0){
                pr = round((ur / .1934));
                pl = round((ul / .1934));
            }else{
                pr = 0;
                pl = 0;  
            }*/
            motordrive(2,pl);

            motordrive(1,pr);
            tickcnt++;

        }else if (c == 's' && tickcnt != tickmax){
            vz = 0;
            vx = -.6;
            ul = (-.5*vz*L+vx)/r;
            ur = (.5*vz*L+vx)/r;    
            
            if(vx > 0){
                pr = round((ur / .1937));
                pl = round((ul / .1937));        
            }else if(vx < 0){
                pr = round((ur / .1934));
                pl = round((ul / .1934));
            }else{
                pr = 0;
                pl = 0;  
            }
            motordrive(1, pr);
            motordrive(2, pl);
            tickcnt++;

        }else if(c == 'd' && tickcnt != tickmax){
            vz = -1.5;
            vx = 0;
            ul = (-.5*vz*L+vx)/r;
            ur = (.5*vz*L+vx)/r;    
            
            //if(vx > 0){
                pr = round((ur / .1937));
                pl = round((ul / .1937));        
            /*}else if(vx < 0){
                pr = round((ur / .1934));
                pl = round((ul / .1934));
            }else{
                pr = 0;
                pl = 0;  
            }*/
            motordrive(1, pr);
            motordrive(2, pl);
            tickcnt++;
        }else{
            break;
        }
        
        printf("ur %f, ul %f\n", ur, ul);
        printf("pr %i, pl %i\n", pr, pl);
    }
    motordrive(1, 0);
    motordrive(2, 0);
}


void error(const char *msg)
{
    perror(msg);
    exit(1);
}



int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[25];
     bool user = false;
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     printf("Socket is listening");
     clilen = sizeof(cli_addr);
     while(1){
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) 
            error("ERROR on accept");
        printf("client accepted");
        while(recv(newsockfd, buffer, 25, 0) != 0){
            printf("%s\n",buffer);
            if(buffer[0] == 'u' && user == false){
                printf("override\n");
                user = true;
            }else if(user == true){
                if(buffer[0] == 'w'){
                    printf("forward\n");
                    motorcontrol(buffer[0], 0);
                }else if(buffer[0] == 'a'){
                    printf("Turning Left\n");
                    motorcontrol(buffer[0], 0);
                }else if(buffer[0] == 's'){
                    printf("reverse\n");
                    motorcontrol(buffer[0], 0);
                }else if(buffer[0] == 'd'){
                    printf("Turning Right\n");
                    motorcontrol(buffer[0], 0);
                }else if(buffer[0] == 'u'){
                    printf("exit override\n");
                    user = false;
                }else{
          
                }
            }else{
        
            }
        
            if(buffer[0] == 'q'){
                printf("quit\n");
                close(newsockfd);
                close(sockfd);
                return 0;
            }

        }
     }
     close(newsockfd);
     close(sockfd);
     return 0; 
}
