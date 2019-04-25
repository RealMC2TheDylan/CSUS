/*
    Encoder Left ROS
    computes globalCounter_L
    computes velocity of robot based on encoder ticks
      Output reset to Encoder Right Code
      Input globalCounter_R from Encoder Right Code
*/


#include <ros/ros.h>
#include <std_msgs/Float32.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <time.h>
#include <stdbool.h>
#include <cmath>
//#include "encoderGlobals.h"
 
#define RotateAPin 21 //Define as CLK
#define RotateBPin 22// Define as DT
//#define SwitchPin  23// Define as Push Button Switch

int globalCounter_R; // = 0 ; // pull from ROS Node Encoder R
static volatile int globalCounter_L = 0;
bool reset = false; // pass to encoder R for reset of globalCount_R
 
static unsigned char flag;
static unsigned char Last_RoB_Status;
static unsigned char Current_RoB_Status;
 

void rotaryDeal_L(void)
{
	Last_RoB_Status = digitalRead(RotateBPin);
 
	while(!digitalRead(RotateAPin)){
		Current_RoB_Status = digitalRead(RotateBPin);
		flag = 1;
	}
 
	if(flag == 1){
		flag = 0;
		if((Last_RoB_Status == 0)&&(Current_RoB_Status == 1)){ // forward
			globalCounter_L ++;
		}
		if((Last_RoB_Status == 1)&&(Current_RoB_Status == 0)){ // backward
			globalCounter_L --;
		}
	}
}

 
int main(void)
{
    if(wiringPiSetup() < 0){
		fprintf(stderr, "Unable to initialize wiringPi:%s\n",strerror(errno));
		return 1;
	}
	pinMode(RotateAPin, INPUT);
	pinMode(RotateBPin, INPUT);
   
	clock_t t;
	bool new_t = true;
    float vx, vy, vth, ur, ul,x;
    float r =.1275;
    float L=.420;
    

  	while(1){

		if(new_t == true){
			t = clock();
			new_t = false;
		}

		rotaryDeal_L(); // encoder "interrupt" loop
		
	    if(globalCounter_L==20){
    			t = clock() - t; //time taken
                ul=(globalCounter_L/(float)1536)/(((double)t)/CLOCKS_PER_SEC); // rad/s
                ur=(globalCounter_R/(float)1536)/(((double)t)/CLOCKS_PER_SEC); // rad/s
                vx=(r/2)*(ur+ul); // m/s
                vy = 0; // assumption based upon model
                vth=(r/L)*(ur-ul); // rad/s
                //printf("v: %lf, Vth: %lf\n",vx,vth);
                //publish vx, vy, vth
                new_t = true; // allow new start time
                reset = true; // reset counter R
                globalCounter_L = 0; // reset counter L
            }
      	}
 
	
}
