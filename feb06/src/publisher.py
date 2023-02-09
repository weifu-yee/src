#!/usr/bin/env python3 
#coding:utf-8

import rospy
from std_msgs.msg import Int64
from feb06.msg import message

def publisher():
    rospy.init_node('publisher')
    pub = rospy.Publisher('loc_data', message, queue_size = 10)
    loc = message()
    loc.position.linear.x = 10
    loc.position.linear.y = 10
    loc.position.angular.z = 10
    while not rospy.is_shutdown():
            pub.publish(loc)
            rospy.sleep(2)
            loc.time+=1
    
if __name__=='__main__':
    try:
        publisher()
    except rospy.ROSInterruptException:
        pass