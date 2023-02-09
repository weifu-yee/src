#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Point32.h"
#include "turtlesim/Pose.h"
#include "cmath"
#include "iostream"

//using namespace std;
#define PI 3.1415926

int linear_velocity, angular_velocity;
float x, y,theta;
float x_1, y_1, theta_1;
int step = 0;
float diff;


void Callback(const turtlesim::Pose::ConstPtr& the_pose)
{
    x = the_pose->x;
    y = the_pose->y;
    theta = the_pose->theta;

}

float angle(float destination_x, float destination_y){
    float angle;
    angle = std::atan( destination_y - y / destination_x - x );

    std::cout<<"abs:"<<angle<<"  ";

    diff = angle - theta;

    while(diff > PI )       diff -= 2 *PI;      
    while(diff < -1 * PI )      diff += 2 * PI;

    std::cout<<"diff:"<<diff<<"\t";

    return diff;
}

geometry_msgs::Twist GoToPoint(float destination_x, float destination_y){
    geometry_msgs::Twist speed;


        if(theta >= 2 * PI - 0.03 || theta <= PI / 2 - 0.03)   step = 0;
        else if(theta >= PI / 2 - 0.03 && theta <= PI - 0.03)   step = 1;
        else if(theta >= PI - 0.03 && theta <= 3 * PI / 2 - 0.03)   step = 2;
        else   step = 3;

        if(step_last != step){
            goal_ang = theta + PI / 2;
            step_last = step;
        }

    speed.angular.z = angle(destination_x,destination_y);
    // if(speed.angular.z < -1 * PI){
    //     speed.angular.z += 2*PI;
    // }

    std::cout<<speed.angular.z<<"\t"<<"step : "<<step<<"\n";

    speed.linear.x = 1 * std::abs(destination_x - x);


    // speed.linear.x = 1;

    return speed;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "follow");
    ros::NodeHandle nh;
    ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
    ros::Subscriber pose_sub = nh.subscribe("turtle1/pose",10,Callback);
    ros::Rate loop_rate(1);
    
    while(ros::ok())
    {
        ros::spinOnce();
        if(step == 0){
            vel_pub.publish( GoToPoint(8,2) );
            if(x >= 8 )    step++, step %= 4;
        }
        if(step == 1){
            vel_pub.publish( GoToPoint(3,6) );
            if(y >= 6)    step++, step %= 4;
        }
        if(step == 2){
            vel_pub.publish( GoToPoint(4,7) );
            if(x <= 4)    step++, step %= 4;
        }
        if(step == 3){
            vel_pub.publish( GoToPoint(5,2) );
            if(y <= 2)    step++, step %= 4;
        }
    }
    return 0;
}

