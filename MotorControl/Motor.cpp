#include <wiringSerial.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int fd = serialOpen("/dev/ttySAC0", 38400);

int constrain(int power, int low, int high) {
	if (power > high) {
		power = high;
	}
	else if (power < low) {
		power = low;
	}
	else
		return power;
}

void motordrive(int motor, int power)
{
	char command;
	char magnitude;
	power = constrain(power, -63, 63);
	if (motor == 1)
	{
		command = 64 + power;
	}
	else if (motor == 2)
	{
		command = 191 + power; // changed from 190 and 191
	}

	serialPuts(fd, &command);
	serialPuts(fd, &command);
}

int main(){
    int p; 
    char s;
    while(1)
    {   
        printf("input '+/-''int' with no spaces: ");
        scanf("%c %i",&s,&p);
        if(s=='-'){
            p=-p;}        
        motordrive(1,p);
        motordrive(2,p);
        if(p==0){
            return 0;
        }
    }
    delay(2000);
}