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

int main(int argc, char** argv)
{
	ros::init(argc, argv, "velocity_computation_node");
	ros::NodeHandle n;
	ros::Publisher velocity_pub = n.advertise<std::msgs::Float32MultiArray>("vx_vy_vth", 3);
	std_msgs::Float32MultiArray vx0_vy1_vth3;

	ros::Subscriber sub = n.subscriber("globalCounter_R", 1, ***);
	ros::Subscriber sub = n.subscriber("globalCounter_L", 1, ***);
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