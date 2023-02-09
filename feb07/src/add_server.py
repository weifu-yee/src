#!/usr/bin/env python3
#coding:utf-8

import rospy
from feb07.srv import *

def server():
    rospy.init_node("add_server")
    s = rospy.Service("add_two_number_py",test,handle_function)
    rospy.loginfo("waiting to request")
    rospy.spin()

def handle_function(req):
    rospy.loginfo("two number are %lf and %lf" , req.a, req.b)
    return testResponse(req.a+req.b)

if __name__=="__main__":
    server();