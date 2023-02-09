#include <ros/ros.h>
#include <feb07/test.h>

int main(int argc, char **argv)
{
    ros::init(argc,argv,"add_client");
    ros::NodeHandle nh;
    ros::ServiceClient client = nh.serviceClient<feb07::test>("add_two_number");
    feb07::test srv;
    while(ros::ok()){
        std::cout<<"a = ";
        std::cin>>srv.request.a;
        std::cout<<"b = ";
        std::cin>>srv.request.b;

        if(client.call(srv)){
            std::cout<<"The response is "<<srv.response.c<<"\n";
        }
        else{
            std::cout<<"Failed to call service\n";
        }
    }
    return 0;
}