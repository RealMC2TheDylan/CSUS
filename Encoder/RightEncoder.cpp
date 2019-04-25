/*
    Encoder Right ROS
    computes globalCounter_R
    resets globalCounter_R if reset = True
      Output globalCounter_R to Encoder Left Code for vel computations
      Input reset from Encoder Left Code
*/

#include <ros/ros.h>                                   /* Edited by Kaicha */
#include <std_msgs/Int32.h>                          /* 04/24/19   */                              
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
int reset = 0;                      // Temporary
 
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

 
int main(int argc, char** argv)
{
    /* Edited by Kaicha */
    ros::init(argc, argv, "encoder_pkg_rightEncoder_node");  
    ros::NodeHandle n;
    ros::Publisher encoderR_pub = n.advertise<std_msgs::Int32>("global_counter_r", 1);
    std_msgs::Int32 global_counter_r_value;
    ros::Rate r(20.0);
    /* 04/24/19         */





    if(wiringPiSetup() < 0){
		fprintf(stderr, "Unable to initialize wiringPi:%s\n",strerror(errno));
		return 1;
	}

	pinMode(RotateAPinR, INPUT);
	pinMode(RotateBPinR, INPUT);

  	while(n.ok()){

		rotaryDeal();
		
	    if(reset == true){ // reset if told to by Encoder Left Code
            globalCounter_R=0;
            reset=false;
        }
        



        /* Edited by Kaicha */
        global_counter_r_value.data = globalCounter_R;
        encoderR_pub.publish(global_counter_r_value);         
    }
}
