/*
	Encoder Right Ros v2.0
	compute ur to send to a velocity node
*/

#include <ros/ros.h>						//ROS Specific Headers         
#include <std_msgs/Int32.h>   

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h> 
#include <time.h>
#include <stdbool.h>
#include <cmath>


#define RotateAPinR 0 //CLK pin
#define RotateBPinR 1// DT(data) pin

static volatile int globalCounter_R = 0;

static unsigned char flag;
static unsigned char Last_RoB_Status;
static unsigned char Current_RoB_Status;

void rotaryDeal(void)
{
	Last_RoB_Status = digitalRead(RotateBPinR);

	while (!digitalRead(RotateAPinR)) {
		Current_RoB_Status = digitalRead(RotateBPinR);
		flag = 1;
	}

	if (flag == 1) {
		flag = 0;
		if ((Last_RoB_Status == 0) && (Current_RoB_Status == 1)) { // forward
			globalCounter_R++;
		}
		if ((Last_RoB_Status == 1) && (Current_RoB_Status == 0)) { // backward
			globalCounter_R--;
		}
	}
}


int main(int argc, char** argv)
{
	ros::init(argc, argv, "encoder_pkg_rightEncoder_node");
	ros::NodeHandle n;
	ros::Publisher encoderR_pub = n.advertise<std_msgs::Float32>("global_counter_r", 1);
	std_msgs::Float32 global_counter_r_value;
	ros::Rate r(20.0);
	





	if (wiringPiSetup() < 0) {
		fprintf(stderr, "Unable to initialize wiringPi:%s\n", strerror(errno));
		return 1;
	}

	pinMode(RotateAPinR, INPUT);
	pinMode(RotateBPinR, INPUT);

	while (n.ok()) {

		rotaryDeal();

		ros::spinOnce();

		global_counter_r_value.data = globalCounter_R;
		encoderR_pub.publish(global_counter_r_value);

		globalCounter_R = 0;
		
		
	}
		
	
}
