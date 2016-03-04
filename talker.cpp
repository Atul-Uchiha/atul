
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int8.h"
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

#include <sstream>


using namespace cv;
using namespace std;

typedef struct tag
{
int x, y;
}point;

Mat  pic = imread("ps1.jpg", 1);
Mat img = imread("ps1.jpg", 0);
Mat path = imread("ps1.jpg", 0);
int visited[500][1000] = { 0 };
int main(int argc, char **argv)
{

  int p[1000]={0}, q[1000]={0};
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher abscissa_pub = n.advertise<std_msgs::Int16>("chatter1", 1000);
  ros::Publisher ordinate_pub = n.advertise<std_msgs::Int16>("chatter2", 1000);
  ros::Rate loop_rate(10);
  int count = 0;
	stack<point>s;
	point start = { 31, 27 };
	s.push(start);
	visited[start.x][start.y] = 1;
 	int i,j;
	point present;
	point temp;

for(int c1=0; !s.empty(); c1++)
{
	present = s.top();
		i = present.x; j = present.y;

		s.pop();
		if (i > 160 && i<168 && j > 166 && j<174) break;
		if (i>7 && j > 7 && i < pic.cols - 7 && j < pic.rows - 7)
		{
			p[c1]=i; q[c1]=j;
			if (img.at<uchar>(i, j - 1) < 200 && !(visited[i][j - 1]))
			{temp.x=i; temp.y=j-1;		s.push(temp); visited[i][j - 1] = 1;	}
			if (img.at<uchar>(i - 1, j+1) < 200  && !(visited[i - 1][j+1]))
			{temp.x=i-1; temp.y=j+1;	s.push(temp); visited[i - 1][j+1] = 1;}
			if (img.at<uchar>(i, j + 1) < 200 && !(visited[i][j + 1]))
			{temp.x=i; temp.y=j+1;	s.push(temp); visited[i][j + 1] = 1;}
			if (img.at<uchar>(i - 1, j-1) < 200 && !(visited[i - 1][j-1]))
			{temp.x=i-1; temp.y=j-1;	s.push(temp); visited[i - 1][j-1] = 1;}
			if (img.at<uchar>(i + 1, j) < 200  && !(visited[i + 1][j]) )
			{temp.x=i+1; temp.y=j;		s.push(temp); visited[i + 1][j] = 1;}
			if (img.at<uchar>(i + 1, j-1) < 200 && !(visited[i + 1][j-1]))
			{temp.x=i+1; temp.y=j-1;	s.push(temp); visited[i + 1][j-1] = 1;}
			if (img.at<uchar>(i - 1, j) < 200 && !(visited[i - 1][j]))
			{temp.x=i-1; temp.y=j;		s.push(temp); visited[i - 1][j] = 1;}
			if (img.at<uchar>(i + 1, j+1) < 200 && !(visited[i + 1][j+1]))
			{temp.x=i+1; temp.y=j+1;	s.push(temp); visited[i + 1][j+1] = 1;}
		path.at<uchar>(i,j)=255;
	}
}
	for(int c2=0; ros::ok(); c2++)
	{
		std_msgs::Int16  msg_x;
		std_msgs::Int16  msg_y;
		msg_x.data=p[c2];
		msg_y.data=q[c2];
    		ROS_INFO("Abscissa = %d", msg_x.data);
   		ROS_INFO("Ordinate = %d", msg_y.data);
    		abscissa_pub.publish(msg_x);
		ordinate_pub.publish(msg_y);
   		ros::spinOnce();
    		loop_rate.sleep();
    		++count;
	}
	return 0;
}
