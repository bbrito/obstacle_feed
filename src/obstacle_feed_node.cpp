#include <ros/ros.h>
#include <obstacle_feed/obstacle_feed.h>

int main(int argc, char **argv)
{
  try
  {
    ros::init(argc, argv,"obstacle_feed");
    
    ObstacleFeed obstacles;

    if(!obstacles.initialize())
    {
      ROS_ERROR_STREAM_NAMED("FAILED TO INITIALIZE %s", ros::this_node::getName().c_str());
      exit(1);
    }
    else{
      ROS_INFO_STREAM_NAMED("%s INITIALIZED SUCCESSFULLY!", ros::this_node::getName().c_str());
      ros::spin();
    }
  }

  catch (ros::Exception& e)
  {
    ROS_ERROR("obstacle_feed_node: Error occured: %s", e.what());
    exit(1);
  }  

  return 0;
}
