#include "ros/ros.h"
#include "std_msgs/Int64.h"
#include "feb06/message.h"

void Callback(const feb06::message::ConstPtr& msg)
{
    std::cout<<"msg.time = "<<msg->time<<"\n";
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "subscriber");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/loc_data",10,Callback);
    ros::Rate loop_rate(1);
    
    while(ros::ok())
    {
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
