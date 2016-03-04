
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
#include<typeinfo>
#include<math.h>
#include "opencv/cv.h"
#include<unistd.h>
#include<sys/ioctl.h>
#include<fcntl.h>
#include<termios.h>
#include<stdio.h>
#include<bits/stdc++.h>
#include<stack>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <std_msgs/Int8.h>

void chatterCallback_x(const std_msgs::Int16::ConstPtr& msg_x)
{
ROS_INFO("I heard: abscsisa [%d]", msg_x->data);
}

void chatterCallback_y(const std_msgs::Int16::ConstPtr& msg_y)
{
ROS_INFO("I heard: ordinate [%d]", msg_y->data);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber sub_x = n.subscribe("chatter1", 1000, chatterCallback_x);
  ros::Subscriber sub_y = n.subscribe("chatter2", 1000, chatterCallback_y);
  ros::spin();
  return 0;
}


