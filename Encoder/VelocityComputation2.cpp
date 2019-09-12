/*
	Velocity Computation v1.0
	receives angular velocities
	computes translational velocities and sends to navigation
*/

#include <ros/ros.h>                                   
#include <std_msgs/Int32.h> 
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
	ros::init(argc, argv, "encoder_pkg_velocityComputation_node");
	ros::NodeHandle n;
	ros::Publisher velocity_pub_vx = n.advertise<std_msgs::Float32>("v_x", 1);
	ros::Publisher velocity_pub_vy = n.advertise<std_msgs::Float32>("v_y", 1);
	ros::Publisher velocity_pub_vth = n.advertise<std_msgs::Float32>("v_th", 1);
	
	std_msgs::Float32 v_x_value;
	std_msgs::Float32 v_y_value;
	std_msgs::Float32 v_th_value;


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

		v_x_value.data = vx;
		v_y_value.data = vy;
		v_th_value.data = vth;
		
		velocity_pub_vx.publish(v_x_value);
		velocity_pub_vy.publish(v_y_value);
		velocity_pub_vth.publish(v_th_value);
		
	}
}