/*
Kaicha Johnson 04/06/19

robot_setup_pkg_base_controller_node:

--subscribes to the cmd_vel topic that sends geometry_msgs/Twist messages

--The Navigation stack assumes it can send velocity commands to this node
via the cmd_vel topic

--processes message and sends to Morgan's motor control

--May read encoders and publish state to appropriate topic


*/

#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>



void twistCallback (const geometry_msgs::Twist &twist) {
    //send twist.linear.x and twist.angular.z to motor control
    
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
    std::cout << "testing" << std::endl;
    ros::Rate loop_rate(50);        /*-------------config-----------------*/
    
    while (ros::ok()) {
        ros::spinOnce();
        loop_rate.sleep();
    }
}
