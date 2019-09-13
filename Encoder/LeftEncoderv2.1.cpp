/*
	Encoder Left Ros v2.0
	compute ul to send to a velocity node
*/

#include <ros/ros.h>						//ROS specific Headers
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

#define RotateAPin 21 //CLK pin
#define RotateBPin 22 //DT(data) pin

static volatile int globalCounter_L = 0;

static unsigned char flag;
static unsigned char Last_RoB_Status;
static unsigned char Current_RoB_Status;

void rotaryDeal_L(void)
{
	Last_RoB_Status = digitalRead(RotateBPin);

	while (!digitalRead(RotateAPin)) {
		Current_RoB_Status = digitalRead(RotateBPin);
		flag = 1;
	}

	if (flag == 1) {
		flag = 0;
		if ((Last_RoB_Status == 0) && (Current_RoB_Status == 1)) { // forward
			globalCounter_L++;
		}
		if ((Last_RoB_Status == 1) && (Current_RoB_Status == 0)) { // backward
			globalCounter_L--;
		}
	}
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "encoder_pkg_leftEncoder_node");
	ros::NodeHandle n;
	ros::Publisher encoderL_pub = n.advertise<std_msgs::Int32>("global_counter_l",1);
	std_msgs::Int32 global_counter_l_value;

	ros::Rate w(20.0);
	//ROS intialization

	if (wiringPiSetup() < 0) {
		fprintf(stderr, "Unable to initialize wiringPi:%s\n", strerror(errno));
		return 1;
	}

	pinMode(RotateAPin, INPUT);
	pinMode(RotateBPin, INPUT);
	//Encoder Intialization


	while (n.ok())
	{
		rotaryDeal_L();


		global_counter_l_value.data = globalCounter_L;
		encoderL_pub.publish(global_counter_l_value);
			
		//globalCounter_L = 0;
			
		
	}
}