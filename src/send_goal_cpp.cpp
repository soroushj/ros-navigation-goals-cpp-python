#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){

  ros::init(argc, argv, "send_goal_cpp");

  MoveBaseClient client("move_base", true);

  ROS_INFO("Waiting for the action server to start");
  client.waitForServer();

  ROS_INFO("Action server started, sending the goal");
  move_base_msgs::MoveBaseGoal goal;
  goal.target_pose.header.stamp = ros::Time::now();

  // set frame
  goal.target_pose.header.frame_id = "map";

  // set position
  goal.target_pose.pose.position.x = 1.0;
  goal.target_pose.pose.position.y = 1.0;
  goal.target_pose.pose.position.z = 0.0;

  // set orientation
  goal.target_pose.pose.orientation.x = 0.0;
  goal.target_pose.pose.orientation.y = 0.0;
  goal.target_pose.pose.orientation.z = 1.0;
  goal.target_pose.pose.orientation.w = 0.0;

  client.sendGoal(goal);

  ROS_INFO("Waiting for the result");
  client.waitForResult();

  if (client.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("Succeeded");
  } else {
    ROS_INFO("Failed");
  }

  return 0;
}
