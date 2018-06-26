#ifndef OBSTACLE_FEED_CONFIGURATION_H
#define OBSTACLE_FEED_CONFIGURATION_H

#include <ros/ros.h>

#include <string>

using namespace std;

class obstacle_feed_configuration
{

public:

    obstacle_feed_configuration();

    ~obstacle_feed_configuration();

    bool initialize();
    bool updateConfiguration();
    bool initialize_success_;
    bool activate_output_;

    string obstacle_base_link_;
    string pub_ellipse_topic_;
    string pub_visualization_topic_;

    int obstacle_feed_mode_;

    double distance_threshold_;
    double max_obstacle_radius_;

    int obstacle_threshold_;

    int update_rate_;

    std::vector<double> obst_pose_x_;
    std::vector<double> obst_pose_y_;
    std::vector<double> obst_pose_heading_;
    std::vector<double> obst_dim_minor_;
    std::vector<double> obst_dim_major_;


private:

    void free_allocated_memory();

    void print_configuration_parameter();

};

#endif //OBSTACLE_FEED_CONFIGURATION_H