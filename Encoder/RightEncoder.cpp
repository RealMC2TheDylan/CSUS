/*
    Encoder Right ROS
    computes globalCounter_R
    resets globalCounter_R if reset = True
      Output globalCounter_R to Encoder Left Code for vel computations
      Input reset from Encoder Left Code
*/


#include <ros/ros.h>
#include <std_msgs/Float32.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h> // not sure if necessary
#include <time.h>
#include <stdbool.h>
//#include "encoderGlobals.h"
 
#define RotateAPinR 0 //Define as CLK
#define RotateBPinR 1// Define as DT
  
static unsigned char flag;
static unsigned char Last_RoB_Status;
static unsigned char Current_RoB_Status;

int globalCounter_R = 0 ;
 
void rotaryDeal(void)
{
	Last_RoB_Status = digitalRead(RotateBPinR);
 
	while(!digitalRead(RotateAPinR)){
		Current_RoB_Status = digitalRead(RotateBPinR);
		flag = 1;
	}
 
	if(flag == 1){
		flag = 0;
		if((Last_RoB_Status == 0)&&(Current_RoB_Status == 1)){ // forward
			globalCounter_R ++;
		}
		if((Last_RoB_Status == 1)&&(Current_RoB_Status == 0)){ // backward
			globalCounter_R --;
		}
	}
}

 
int main(void)
{
    if(wiringPiSetup() < 0){
		fprintf(stderr, "Unable to initialize wiringPi:%s\n",strerror(errno));
		return 1;
	}

	pinMode(RotateAPinR, INPUT);
	pinMode(RotateBPinR, INPUT);

  	while(1){

		rotaryDeal();
		
	    if(reset == true){ // reset if told to by Encoder Left Code
            globalCounter_R=0;
            reset=false;
        }
    }
}