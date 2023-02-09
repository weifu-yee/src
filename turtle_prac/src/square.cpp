#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Point32.h"
#include "turtlesim/Pose.h"
#include "cmath"
#include "iostream"

//using namespace std;
#define PI 3.1415926

float x, y,theta;
int step = 0, step_last = -1;
int minor_step = 0;

float bigx = 11, bigy = 11;
float smallx = 0, smally = 0;
bool k = true;

void Callback(const turtlesim::Pose::ConstPtr& the_pose)
{
    x = the_pose->x;
    y = the_pose->y;
    theta = the_pose->theta;
    if(theta < 0)   theta += 2*PI;
}

geometry_msgs::Twist GoToPoint(float destination_x, float destination_y){
    geometry_msgs::Twist speed;
    float diff, ang;

    std::cout<<"x: "<<x<<"\ty: "<<y<<"\ttheta: "<<theta;

    if(minor_step == 0){
        if(step == 0 || step == 2)  diff = destination_x - x;
        else    diff = destination_y - y;
        if(step == 2 || step == 3)    diff *= -1;
        speed.linear.x = 50 * diff;
        if(std::abs(diff) <= 0.000001)   minor_step = 1;

        
    }

    else if(minor_step == 1){
        if(step == 0)   ang = PI / 2;        else if(step == 1)  ang = PI;
        else if(step == 2)  ang = -1 * PI / 2;        else if(step == 3)  ang = 0;
        diff = ang - theta;
        while(diff > PI )       diff -= 2 *PI;      
        while(diff < -1 * PI )      diff += 2 * PI;

        speed.angular.z = 50 * diff;
        if(std::abs(diff) <= 0.000001){
            minor_step = 0;
            step += 1;
            step %= 4;
        }
    }

    std::cout<<"\t\tstep: "<<step<<"\tminor: "<<minor_step<<"\n";
    return speed;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "square");
    ros::NodeHandle nh;
    ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
    ros::Subscriber pose_sub = nh.subscribe("turtle1/pose",10,Callback);
    ros::Rate loop_rate(1);
    
    while(ros::ok()){   
        ros::spinOnce();

        if(step == 0){
            vel_pub.publish( GoToPoint(bigx,smally) );
        }
        if(step == 1){
            vel_pub.publish( GoToPoint(bigx,bigy) );
        }
        if(step == 2){
            vel_pub.publish( GoToPoint(smallx,bigy) );
        }
        if(step == 3){
            vel_pub.publish( GoToPoint(smallx,smally) );
        }

        //cool
        if(step != step_last){
            step_last = step;
            if(bigx > 0.3 && k){
                bigx -= 0.1;    bigy -= 0.1;    smallx += 0.1;      smally += 0.1;
            }else{
                k = false;
                bigx += 0.1;    bigy += 0.1;    smallx -= 0.1;      smally -= 0.1;
                if(bigx > 10.8)   k = true;
            }
        }
    }
    return 0;
}

