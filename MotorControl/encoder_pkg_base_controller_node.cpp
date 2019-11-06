/*
Kaicha Johnson 04/06/19
robot_setup_pkg_base_controller_node:
--subscribes to the cmd_vel topic that sends geometry_msgs/Twist messages
--The Navigation stack assumes it can send velocity commands to this node
via the cmd_vel topic
--processes message and sends to Morgan's motor control
--May read encoders and publish state to appropriate topic
*/


#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <wiringSerial.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>




const int fd = serialOpen("/dev/ttySAC0", 38400);
double vx, vth;




void twistCallback (const geometry_msgs::Twist &twist) {
    vx = twist.linear.x;
    vth = twist.angular.z; 
}







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


//void initCmdVelSubscriber() {
    
//ros::Subscriber<geometry_msgs::Twist> *cmd_sub = new ros::Subscriber<geometry_msgs::Twist>("cmd_vel", 10, &twistCallback);
//    n.subscribe(*cmd_sub);
//}


int main(int argc, char **argv) {
    
    ros::init(argc, argv, "robot_setup_pkg_base_controller_node");
    ros::NodeHandle n;
    ros::Subscriber cmd_sub = n.subscribe("cmd_vel", 10, &twistCallback);
 

   //initCmdVelSubscriber();    
    int motor;
	int pr,pl;
	double ul, ur;
	double L, r;
		
	L = .420;
    r=.1275;

	motordrive(1, 0);
	motordrive(2, 0);
    ros::Rate loop_rate(50);        
    
    while (ros::ok()) {
        ros::spinOnce();
        

        ul = (-0.5*vth*L+vx)/r;
		ur = (0.5*vth*L+vx)/r;
        
		
		if (vx > 0) {
			pr = round((ur / .1937));
            pl = round((ul / .1937));
		}
		else if (vx < 0) {
			pr = round((ur / .1934));
            pl = round((ul / .1934));
		}
		else {
			pr = 0;
            pl = 0;
	    }
		motordrive(1, pr);
		motordrive(2, pl);
        loop_rate.sleep();
    }
    motordrive(1, 0);

	motordrive(2, 0);


}



/*
int main()
{
	
    while(1){	     
    	
	}
	motordrive(1, 0);
	motordrive(2, 0);
}
*/