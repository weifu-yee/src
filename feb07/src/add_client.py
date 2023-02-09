#!/usr/bin/env python3
#coding:utf-8

import rospy
from feb07.srv import *

def client(a,b):
    rospy.init_node("add_client")
    rospy.loginfo("a = %lf, b = %lf",a,b)
    rospy.wait_for_service("add_two_number_py")
    try:
        test_client = rospy.ServiceProxy("add_two_number_py",test)
        resp = test_client(a,b)
        rospy.loginfo("The response is %lf", resp.c)
    except rospy.ServiceException:
        rospy.logwarn("Service call failde")


if __name__=="__main__":
    a = 1
    b = 2
    client(a,b);