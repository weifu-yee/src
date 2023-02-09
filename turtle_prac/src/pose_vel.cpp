#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"

int linear_velocity, angular_velocity;
float x, y,theta, ang_spd;
float x_1, y_1, theta_1;
int step = 0;

const float minus90 = -1.570785;

void Callback(const turtlesim::Pose::ConstPtr& the_pose)
{
    x = the_pose->x;
    y = the_pose->y;
    theta = the_pose->theta;
    // linear_velocity = the_pose->linear_velocity;
    // angular_velocity = the_pose->angular_velocity;

    if(step == 0 && x >= 10.00000) step = 1;
    if(step == 1 && theta <= minus90)   step = 2;
    if(step == 2 && y <= 0.00000) step = 3;

    x_1 = 1 * (10 - x + 0.01);
    y_1 = 1 * (y - 0 + 0.01);
    theta_1 = -1 * (theta - minus90 + 0.01);

    ROS_INFO("x:%f , y:%f , theta:%f , step:%d",x,y,theta,step);
    ROS_INFO("\nx_1:%f , y_1:%f , theta_1:%f",x_1,y_1,theta_1);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "pose_vel");
    ros::NodeHandle nh;
    ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
    ros::Subscriber pose_sub = nh.subscribe("turtle1/pose",10,Callback);
    geometry_msgs::Twist the_vel;

    ros::Rate loop_rate(1);
    
    while(ros::ok())
    {
        ros::spinOnce();

        if(step == 0){
            the_vel.linear.x = x_1;
        }else if(step == 1){
            the_vel.linear.x = 0;
            the_vel.angular.z = theta_1;
        }else if(step == 2){
            the_vel.angular.z = 0;
            the_vel.linear.x = y_1;
        }else{
            the_vel.linear.x = 0;
            break;
        }

        vel_pub.publish(the_vel);
        
    }
    return 0;
}

