#include "ros/ros.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <std_msgs/Int32MultiArray.h>
#include "robot_world_state/world_state.h"



class sub_class{
    public:
        void big_sub_callback(const robot_world_state::world_state::ConstPtr& msg);
        void small_sub_callback(const robot_world_state::world_state::ConstPtr& msg);       
        void and_gate();
        sub_class();
        ~sub_class(){};

    private:
        ros::NodeHandle n;
		ros::Subscriber big_sub = n.subscribe<robot_world_state::world_state>("rx_big", 1, &sub_class::big_sub_callback,this);
        ros::Subscriber small_sub = n.subscribe<robot_world_state::world_state>("rx_small", 1, &sub_class::small_sub_callback,this);
        ros::Publisher pub_ = n.advertise<robot_world_state::world_state>("pub_world_state",1);
        robot_world_state::world_state small;
        robot_world_state::world_state big;
        robot_world_state::world_state whole;
};
sub_class::sub_class(){
    whole.lighthouse_done = false ;
    whole.flag_done = false ;
}
void sub_class::big_sub_callback(const robot_world_state::world_state::ConstPtr& msg){
    big.lighthouse_done = msg->lighthouse_done;
    big.flag_done = msg->flag_done;
}
void sub_class::small_sub_callback(const robot_world_state::world_state::ConstPtr& msg){
    small.lighthouse_done = msg->lighthouse_done;
    small.flag_done = msg->flag_done;
}
void sub_class::and_gate(){
    if(small.lighthouse_done==true||small.lighthouse_done==true)
        whole.lighthouse_done = true ; 
    if(small.flag_done==true||small.flag_done==true)
        whole.flag_done = true ; 

    pub_.publish(whole);
}
int main(int argc, char **argv){
    ros::init(argc,argv, "world_state");
    sub_class temp;
    while(ros::ok()){
        temp.and_gate();
        ros::spinOnce();
    }
}


