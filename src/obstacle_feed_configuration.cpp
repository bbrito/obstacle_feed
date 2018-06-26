#include <obstacle_feed/obstacle_feed_configuration.h>

obstacle_feed_configuration::obstacle_feed_configuration()
{
    initialize_success_ = false;
}

obstacle_feed_configuration::~obstacle_feed_configuration()
{
    free_allocated_memory();
}

bool obstacle_feed_configuration::initialize()
{
    ros::NodeHandle nh_config;
    ros::NodeHandle nh;

    // read parameter from parameter server if not set than terminate code, as this parameter is essential parameter
    if (!nh.getParam ("obstacle_feed_mode", obstacle_feed_mode_) )
    {
        ROS_WARN(" Parameter 'obstacle_feed_mode' not set on %s node " , ros::this_node::getName().c_str());
        return false;
    }

    // read parameter from parameter server if not set than terminate code, as this parameter is essential parameter
    if (!nh.getParam ("obstacle_base_link", obstacle_base_link_) )
    {
      ROS_WARN(" Parameter 'obstacle_base_link' not set on %s node " , ros::this_node::getName().c_str());
      return false;
    }

    // read parameter from parameter server if not set than terminate code, as this parameter is essential parameter
    if (!nh.getParam ("distance_threshold", distance_threshold_) )
    {
        ROS_WARN(" Parameter 'distance_threshold' not set on %s node " , ros::this_node::getName().c_str());
        return false;
    }

    // read parameter from parameter server if not set than terminate code, as this parameter is essential parameter
    if (!nh.getParam ("obstacle_threshold", obstacle_threshold_) )
    {
        ROS_WARN(" Parameter 'obstacle_threshold' not set on %s node " , ros::this_node::getName().c_str());
        return false;
    }

    // read parameter from parameter server if not set than terminate code, as this parameter is essential parameter
    if (!nh.getParam ("max_obstacle_radius", max_obstacle_radius_) )
    {
        ROS_WARN(" Parameter 'max_obstacle_radius' not set on %s node " , ros::this_node::getName().c_str());
        return false;
    }

    // read parameter from parameter server if not set than terminate code, as this parameter is essential parameter
    if (!nh.getParam ("update_rate", update_rate_) )
    {
        ROS_WARN(" Parameter 'update_rate' not set on %s node " , ros::this_node::getName().c_str());
        return false;
    }

    // read parameter from parameter server if not set than terminate code, as this parameter is essential parameter
    if (!nh.getParam ("pub_ellipse_topic", pub_ellipse_topic_) )
    {
        ROS_WARN(" Parameter 'pub_ellipse_topic' not set on %s node " , ros::this_node::getName().c_str());
        return false;
    }

    // read parameter from parameter server if not set than terminate code, as this parameter is essential parameter
    if (!nh.getParam ("pub_visualization_topic", pub_visualization_topic_) )
    {
        ROS_WARN(" Parameter 'pub_visualization_topic' not set on %s node " , ros::this_node::getName().c_str());
        return false;
    }

    if (!nh_config.getParam ("predefined_obstacles/pose_x", obst_pose_x_) )
    {
        ROS_WARN(" Parameter '/predefined_obstacles/pose_x not set on %s node" , ros::this_node::getName().c_str());
        return false;
    }

    if (!nh_config.getParam ("predefined_obstacles/pose_y", obst_pose_y_) )
    {
        ROS_WARN(" Parameter '/predefined_obstacles/pose_y not set on %s node" , ros::this_node::getName().c_str());
        return false;
    }

    if (!nh_config.getParam ("predefined_obstacles/heading", obst_pose_heading_) )
    {
        ROS_WARN(" Parameter '/predefined_obstacles/pose_x not set on %s node" , ros::this_node::getName().c_str());
        return false;
    }

    if (!nh_config.getParam ("predefined_obstacles/dimensions/minor_semiaxis", obst_dim_minor_) )
    {
        ROS_WARN(" Parameter '/predefined_obstacles/dimensions/minor_semiaxis not set on %s node" , ros::this_node::getName().c_str());
        return false;
    }

    if (!nh_config.getParam ("predefined_obstacles/dimensions/major_semiaxis", obst_dim_major_) )
    {
        ROS_WARN(" Parameter '/predefined_obstacles/dimensions/major_semiaxis not set on %s node" , ros::this_node::getName().c_str());
        return false;
    }

    ROS_WARN(" OBSTACLE FEED PARAMETER INITIALIZED!!");
    return true;
}

void obstacle_feed_configuration::free_allocated_memory()
{

}
