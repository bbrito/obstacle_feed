#ifndef OBSTACLE_FEED_H
#define OBSTACLE_FEED_H

#include <ros/ros.h>
#include <std_msgs/Header.h>
#include <tf/transform_listener.h>
#include <tf/tf.h>

#include <Eigen/Dense>

#include <vector>

#include <autoware_msgs/DetectedObjectArray.h>
#include <jsk_recognition_msgs/BoundingBoxArray.h>

// custom obstacle messages
#include <obstacle_feed/Obstacle.h>
#include <obstacle_feed/Obstacles.h>

// boost includes
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include <obstacle_feed/obstacle_feed_configuration.h>

#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

bool CompareObstacleDistance(obstacle_feed::Obstacle& obst1, obstacle_feed::Obstacle& obst2);

class ObstacleFeed
{
public:

  ObstacleFeed();

  ~ObstacleFeed();

  bool initialize();

  ros::Subscriber obstacles_sub, bounding_boxes_sub;

  ros::Publisher obstacles_pub, bounding_boxes_pub, visualize_obstacles_pub;

  ros::Timer loop_timer;

private:

  ros::NodeHandle nh_;

  tf::TransformListener tf_listener_;

  bool activate_debug_output_;

  boost::shared_ptr<obstacle_feed_configuration> obstacle_feed_config_;

  autoware_msgs::DetectedObjectArray objectArray_;

  jsk_recognition_msgs::BoundingBoxArray boundingBoxes;

  void spinNode();
  void clearDataMember();
  void boundingBoxCallback(const jsk_recognition_msgs::BoundingBoxArray& bb);
  void obstaclesCallback(const autoware_msgs::DetectedObjectArray& objects);
  void updateObstacles(const ros::TimerEvent& event);
  void publishObstacles(const obstacle_feed::Obstacles& obstacles);
  void visualizeObstacles(const obstacle_feed::Obstacles& obstacles);
  void OrderObstacles(obstacle_feed::Obstacles& ellipses);

  obstacle_feed::Obstacle FitEllipse(const autoware_msgs::DetectedObject& object, const double& distance);
  void QuatToZRot(geometry_msgs::Pose& pose);
  void ZRotToQuat(geometry_msgs::Pose& pose);
  bool getTransform(const std::string& from, const std::string& to, Eigen::VectorXd& transform);
  bool transformPose(const std::string& from, const std::string& to, geometry_msgs::Pose& pose);
};

#endif // OBSTACLE_FEED_H