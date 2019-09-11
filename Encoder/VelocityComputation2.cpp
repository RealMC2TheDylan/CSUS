/*
	Velocity Computation v1.0
	receives angular velocities
	computes translational velocities and sends to navigation
*/

#include <ros/ros.h>                                   
#include <std_msgs/int32.h> 
#include <std_msgs/Float32MultiArray.h> 

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h> 
#include <time.h>
#include <stdbool.h>
#include <cmath>

int globalCounter_R;
int globalCounter_L;

void globalCounterRCallback(const std_msgs::Int32::ConstPtr &globalCounter_R_pub) {
	globalCounter_R = globalCounter_R_pub->data;
}

void globalCounterLCallback(const std_msgs::Int32::ConstPtr &globalCounter_L_pub) {
	globalCounter_L = globalCounter_L_pub->data;
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "velocity_computation_node");
	ros::NodeHandle n;
	ros::Publisher velocity_pub = n.advertise<std::msgs::Float32MultiArray>("vx_vy_vth", 3);
	std_msgs::Float32MultiArray vx0_vy1_vth3;

	ros::Subscriber sub = n.subscriber("global_counter_r", 1, globalCounterRCallback);
	ros::Subscriber sub = n.subscriber("global_counter_l", 1, globalCounterLCallback);
	ros::Rate r(20.0);

	float r = .1275;
	float L = .420;

	while (n.ok())
	{
		ros::spinOnce();
		ul = (globalCounter_L / (float)1536) / (1/20); // rad/s
		ur = (globalCounter_R / (float)1536) / (1/20); // rad/s
		vx = (r / 2)*(ur + ul);
		vy = 0;
		vth = (r / L)*(ur - ul);

		vx0_vy1_vth2.data[0] = vx;
		vx0_vy1_vth2.data[1] = vy;
		vx0_vy1_vth2.data[2] = vth;
		velocity_pub.publish(vx0_vy1_vth2);
	}
}