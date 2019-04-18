#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <time.h>
#include <stdbool.h>
 
#define RotateAPin 21 //Define as CLK
#define RotateBPin 22// Define as DT
#define SwitchPin  23// Define as Push Button Switch
 
static volatile int globalCounter = 0 ;
 
unsigned char flag;
unsigned char Last_RoB_Status;
unsigned char Current_RoB_Status;
 
const int fd = serialOpen("/dev/ttySAC0", 38400);

int constrain(int power, int low, int high){
	if(power > high){
		power = high;
	}
	else if(power < low){
		power = low;
	}
	else
	return power;
}
void btnISR(void)
{
	globalCounter = 0;
}
 
void rotaryDeal(void)
{
	Last_RoB_Status = digitalRead(RotateBPin);
 
	while(!digitalRead(RotateAPin)){
		Current_RoB_Status = digitalRead(RotateBPin);
		flag = 1;
	}
 
	if(flag == 1){
		flag = 0;
		if((Last_RoB_Status == 0)&&(Current_RoB_Status == 1)){
			globalCounter ++;
		}
		if((Last_RoB_Status == 1)&&(Current_RoB_Status == 0)){
			globalCounter --;
		}
	}
}

void motordrive(int motor, int power)
{
	char command;
	char magnitude;
	power = constrain(power, -63, 63);
	if (motor == 1)
	{
		command = 64+power;
	}
	else if (motor == 2)
	{
		command = 191+power; // changed from 190 and 191
	}

	//command = constrain(command, 1, 254);
	serialPuts(fd, &command);
    serialPuts(fd, &command);
    //printf("%c\n", command);
}

 
int main(void)
{
	if(wiringPiSetup() < 0){
		fprintf(stderr, "Unable to initialize wiringPi:%s\n",strerror(errno));
		return 1;
	}
 
	pinMode(SwitchPin, INPUT);
	pinMode(RotateAPin, INPUT);
	pinMode(RotateBPin, INPUT);
 
	pullUpDnControl(SwitchPin, PUD_UP);
 
	if(wiringPiISR(SwitchPin, INT_EDGE_FALLING, &btnISR) < 0){
		//fprintf(stderr, "Unable to init ISR\n",strerror(errno));
		return 1;
	}

 	int tickCount = 0;
	int tmp = 0;
	clock_t t;
	double time_taken;
	bool new_t = true;
    int p = -3; //2;
    int x = 0;

    printf("%d ",p);

	while(1){

        motordrive(1, p);

        motordrive(2, p);

		if(new_t == true){
			t = clock();
			new_t = false;
		}
		rotaryDeal();
		//if (tmp != globalCounter){
		//	printf("%d\n", globalCounter);
		//	tmp = globalCounter;
		//}
		if(tmp!=globalCounter){
			tmp=globalCounter;
			tickCount++;
		}

		if(tickCount==100){
			t = clock() - t;
			time_taken = ((double)t)/CLOCKS_PER_SEC;
			printf(", %f ",time_taken);
            tickCount=0;			
            new_t = true;
            x++;
    	}
        if(x==5){
           if(p>-64){//<64){
                p--;//++;
                printf("\n");
                printf("%d ",p);
            }else{
                p=0;
                motordrive(1, p);
                motordrive(2, p);
                printf("\n\n");
                return 0;
            }
          x=0;  
         }
	}
 
	return 0;
}