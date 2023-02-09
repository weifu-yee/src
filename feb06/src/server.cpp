#include "ros/ros.h"
#include "std_msgs/Int64.h"
#include "feb06/server_client.h"

int i = 0;

void Callback(const feb06::server_client::ConstPtr& msg)
{
    if(msg->sender_id == "client"){
        i = msg->last_order;
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "server");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<feb06::server_client>("/ser_cli", 10);
    ros::Subscriber sub = nh.subscribe("/ser_cli",10,Callback);
    //ros::Rate loop_rate(10);
    
    feb06::server_client ser_cli;

    ser_cli.order = 0;
    ser_cli.data = "owo ";
    ser_cli.sender_id = "server";
    //ser_cli.last_order = 0;

    while(ros::ok())
    {   
        ros::spinOnce();
        if(i == ser_cli.order){
            ser_cli.order ++;
            // std::cout<<"order = "<<ser_cli.order<<"\t";
            // std::cout<<"i = "<<i<<"\n";

            //loop_rate.sleep();
        }
        pub.publish(ser_cli);
        if(i == 50) break;
    }
    return 0;
}