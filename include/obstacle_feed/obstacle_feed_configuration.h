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

    string obstacle_base_link_;
    string pub_ellipse_topic_;
    string pub_visualization_topic_;

    int obstacle_feed_mode_;

    double distance_threshold_;
    double max_obstacle_radius_;

    int obstacle_threshold_;

    int update_rate_;

private:

    void free_allocated_memory();

    void print_configuration_parameter();

};

#endif //OBSTACLE_FEED_CONFIGURATION_H