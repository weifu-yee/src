#include "ros/ros.h"
#include "std_msgs/Int64.h"
#include "feb06/server_client.h"

int i = 0;
std::string the_data[50];

void Callback(const feb06::server_client::ConstPtr& msg)
{
    //std::cout<<"received~"<<"\n";
    if(msg->sender_id == "server" && msg->order != i){
        std::cout<<"order = "<<msg->order<<"\t";
        std::cout<<"data = "<<msg->data<<"\n";
        i = msg->order;
        the_data[i-1] = msg->data;
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "client");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<feb06::server_client>("/ser_cli", 10);
    ros::Subscriber sub = nh.subscribe("/ser_cli",10,Callback);
    //ros::Rate loop_rate(1);
    
    int last_i = 0;
    feb06::server_client ser_cli;

    while(ros::ok())
    {
        ros::spinOnce();
        if(i != last_i){
            ser_cli.last_order = i;
            ser_cli.sender_id = "client";
            last_i = i;
        }
        pub.publish(ser_cli);
        if(i == 50){
            std::cout<<"\n";
            for(int j = 1; j <= 50; j++){
                std::cout<<the_data[i-1];
            }
            std::cout<<"\n";
            break;
        }
    }
    return 0;
}
