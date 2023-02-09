#include <ros/ros.h>

int main(int argc, char **argv){
    ros::init(argc,argv,"param_practice");
    ros::NodeHandle nh;
    double freq;

    while(ros::ok()){
        
        nh.getParam("/print_freq",freq);
        ros::Rate rate(freq);
        ROS_INFO("%f", freq);
        rate.sleep();

    }
    return 0;
}