#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Point32.h"
#include "turtlesim/Pose.h"
#include "cmath"
#include "iostream"

#define PI 3.1415926

float x, y,theta;
int step = 0, step_last = -1;
int minor_step = 0;

float bigx = 11, bigy = 11;
float smallx = 0, smally = 0;
bool k = true;

int x_sign = 1, y_sign = 1;

bool if_reach = false;

double speed_Kp, des_x, des_y;
double des_x_last = -1, des_y_last = -1;

void Callback(const turtlesim::Pose::ConstPtr& the_pose)
{
    x = the_pose->x;
    y = the_pose->y;
    theta = the_pose->theta;
    if(theta < 0)   theta += 2*PI;
    std::cout<<"!!!\t";
}

geometry_msgs::Twist GoToPoint(double destination_x, double destination_y, double speed_Kp){
    geometry_msgs::Twist speed;
    double diff, ang;

    if(step == 0){        //angular
        if(destination_x - x >= 0)   ang = 0;        
        else    ang = PI;

        diff = ang - theta;
        while(diff > PI )       diff -= 2 *PI;      
        while(diff < -1 * PI )      diff += 2 * PI;

        speed.angular.z = speed_Kp * diff;
        if(std::abs(diff) <= 0.000001){
            step = 1;
        }
    }
    if(step == 1){       //linear
        diff = destination_x - x;
        if(step_last == 0 && diff < 0)  x_sign = -1;
        diff *= x_sign;
        speed.linear.x = speed_Kp * diff;
        if(std::abs(diff) <= 0.0001)   step = 2;
    }
    if(step == 2){        //angular
        if(destination_y - y >= 0)   ang = PI / 2;        
        else    ang = PI * 3 / 2;

        diff = ang - theta;
        while(diff > PI )       diff -= 2 *PI;      
        while(diff < -1 * PI )      diff += 2 * PI;

        speed.angular.z = speed_Kp * diff;
        if(std::abs(diff) <= 0.0001){
            step = 3;
        }
    }
    if(step == 3){       //linear
        diff = destination_y - y;
        if(step_last == 2 && diff < 0)  y_sign = -1;
        diff *= y_sign;
        speed.linear.x = speed_Kp * diff;
        if(std::abs(diff) <= 0.000001){
            step = 0;
            if_reach = true;
        }
    }
    step_last = step;
    std::cout<<"step: "<<step<<"\tx: "<<x<<"\ty: "<<y;
    return speed;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtle_launch");
    ros::NodeHandle nh;
    ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("abc", 10);
    ros::Subscriber pose_sub = nh.subscribe("turtle1/pose",10,Callback);
    
    while(ros::ok()){
        nh.getParam("/speed",speed_Kp);
        nh.getParam("/des_x",des_x);
        nh.getParam("/des_y",des_y);
        if(des_x_last != des_x || des_y_last != des_y){
            while(!if_reach && ros::ok()){
                ros::spinOnce();
                vel_pub.publish( GoToPoint(des_x, des_y, speed_Kp) );
                std::cout<<"\tdes_x: "<<des_x<<"\tdes_y: "<<des_y;
                std::cout<<"\tspeed_Kp: "<<speed_Kp<<"\n";
            }
            x_sign = 1, y_sign = 1;
            if_reach = false;
        }
        des_x_last = des_x;
        des_y_last = des_y;
    }
    return 0;
}

