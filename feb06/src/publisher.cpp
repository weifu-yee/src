#include "ros/ros.h"
#include "std_msgs/Int64.h"
#include "feb06/message.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "publisher");
    ros::NodeHandle nh;
    ros::Publisher pub_loc = nh.advertise<feb06::message>("/loc_data", 10);
    ros::Rate loop_rate(1);
    
    int number = 0;
    std_msgs::Int64 msg;
    feb06::message loc;

    loc.time = 10;
    loc.position.linear.x = 0;
    loc.position.linear.y = 0;
    loc.position.angular.z = 0;
    
    while(ros::ok())
    {
        loc.time ++;
        pub_loc.publish(loc);
        loop_rate.sleep();
    }
    return 0;
}