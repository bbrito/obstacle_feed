#include <obstacle_feed/obstacle_feed.h>

ObstacleFeed::ObstacleFeed()
{
  ;
}

ObstacleFeed::~ObstacleFeed()
{
  clearDataMember();
}

bool ObstacleFeed::initialize()
{
    if (ros::ok())
    {
        obstacle_feed_config_.reset(new obstacle_feed_configuration());
        bool obstacle_feed_config_success = obstacle_feed_config_->initialize();

        if (obstacle_feed_config_success == false)
        {
            ROS_ERROR("OBSTACLE FEED: FAILED TO INITIALIZE!!");
            return false;
        }

        // Publish ellipses
        obstacles_pub = nh_.advertise<obstacle_feed::Obstacles>(obstacle_feed_config_->pub_ellipse_topic_,1);
        // Publish visualization of ellipses
        visualize_obstacles_pub = nh_.advertise<visualization_msgs::MarkerArray>(obstacle_feed_config_->pub_visualization_topic_,1);

        // Publish obstacles if modus = 1, listen to tracked obstacles otherwise
        if (obstacle_feed_config_->obstacle_feed_mode_ == 1)
        {
            int update_rate = obstacle_feed_config_->update_rate_;
            loop_timer = nh_.createTimer(ros::Duration(1/update_rate), &ObstacleFeed::updateObstacles, this);
        }
        else if (obstacle_feed_config_->obstacle_feed_mode_ == 0) {
            bounding_boxes_pub = nh_.advertise<jsk_recognition_msgs::BoundingBoxArray>("obstacle_bounding_boxes",1);
            obstacles_sub = nh_.subscribe("detected_objects", 1, &ObstacleFeed::obstaclesCallback, this);
            bounding_boxes_sub = nh_.subscribe("cloud_cluster_tracked_bounding_box", 1, &ObstacleFeed::boundingBoxCallback, this);
        }
        else{
            ROS_ERROR("UNDEFINED MODE");
        }

        robotPose.position.x = 0;
        robotPose.position.y = 0;
        robotPose.position.z = 0;

        obstacle_base_link_ = obstacle_feed_config_->obstacle_base_link_;

        return true;
    }
    else
    {
        return false;
    }
}

void ObstacleFeed::spinNode()
{
  ros::spin();
}

void ObstacleFeed::clearDataMember()
{
    ;
}

void ObstacleFeed::obstaclesCallback(const autoware_msgs::DetectedObjectArray& objects)
{
    objectArray_ = objects;

    std::vector<uint32_t> objectIDs;
    std::vector<double> objectDistances;
    double distance;

    autoware_msgs::DetectedObjectArray local_objects;
    obstacle_feed::Obstacles ellipses;
    obstacle_feed::Obstacles local_ellipses;
    obstacle_feed::Obstacle ellipse;

    for (int object_it = 0; object_it < objectArray_.objects.size(); object_it++)
    {

    // Compute distance of obstacle to robot
    distance = sqrt(pow(robotPose.position.x - objectArray_.objects[object_it].pose.position.x,2) + pow(robotPose.position.y - objectArray_.objects[object_it].pose.position.y,2));

      // If distance is smaller than defined bound, add to obstacles
      if (distance < obstacle_feed_config_->distance_threshold_){
       local_objects.objects.push_back(objectArray_.objects[object_it]);
       objectIDs.push_back(objectArray_.objects[object_it].id);
       objectDistances.push_back(distance);
      }
    }

    // For all obstacles, fit an ellipse
    for (int local_obst_it = 0; local_obst_it < local_objects.objects.size(); local_obst_it++)
    {
       ellipse = FitEllipse(local_objects.objects[local_obst_it],objectDistances[local_obst_it]);
       if (ellipse.major_semiaxis < obstacle_feed_config_->max_obstacle_radius_ && ellipse.minor_semiaxis < obstacle_feed_config_->max_obstacle_radius_){
         ellipses.Obstacles.push_back(ellipse);
       }
    }

    // Order obstacles according to distance
    OrderObstacles(ellipses);

    // Transform and add to local obstacles upto a defined bound
    for (int ellipses_it = 0; ellipses_it < obstacle_feed_config_->obstacle_threshold_ && ellipses_it < ellipses.Obstacles.size(); ellipses_it++)
    {
        ZRotToQuat(ellipses.Obstacles[ellipses_it].pose);
        transformPose("base_link","odom",ellipses.Obstacles[ellipses_it].pose);
        QuatToZRot(ellipses.Obstacles[ellipses_it].pose);
        local_ellipses.Obstacles.push_back(ellipses.Obstacles[ellipses_it]);
    }

    // Publish and visualize obstacles
    publishObstacles(local_ellipses);
    visualizeObstacles(local_ellipses);

//    && local_obst_it < obstacle_feed_config_->obstacle_threshold_
//    ROS_INFO_STREAM("Received array of " << objectArray.objects.size() << " objects");
//    ROS_INFO_STREAM("Stored " << objectIDs.size() << " object identities");
//    ROS_INFO_STREAM("Stored " << ellipses.Obstacles.size() << " object identities");
}

void ObstacleFeed::boundingBoxCallback(const jsk_recognition_msgs::BoundingBoxArray& bb)
{
    jsk_recognition_msgs::BoundingBoxArray boundingboxess;
    boundingboxess = bb;

    boundingboxess.header.frame_id = "odom";
//    boundingboxess.header.stamp = ros::Time::now();

    for (int boxes_it = 0; boxes_it < boundingboxess.boxes.size(); boxes_it++)
    {
//        boundingboxess.boxes[boxes_it].header.stamp = ros::Time::now();
        boundingboxess.boxes[boxes_it].header.frame_id = "odom";
    }

    bounding_boxes_pub.publish(boundingboxess);
}

void ObstacleFeed::publishObstacles(const obstacle_feed::Obstacles& obstacles)
{
    obstacles_pub.publish(obstacles);
}

void ObstacleFeed::visualizeObstacles(const obstacle_feed::Obstacles& obstacles) {
    // Initialize markers for visualization
    visualization_msgs::Marker marker;
    visualization_msgs::MarkerArray markerArray;

    // Loop over obstacles in obstacle array
    for (int obst_it = 0; obst_it < obstacles.Obstacles.size(); obst_it++) {
        marker.header.frame_id = obstacle_base_link_;           // Add frame of obstacle
        marker.header.stamp = ros::Time::now();                 // Add timestamp
        marker.id = obst_it;                                    // Obstacle ID
        marker.type = visualization_msgs::Marker::CYLINDER;
        marker.pose = obstacles.Obstacles[obst_it].pose;
        ZRotToQuat(marker.pose);                                // Get Quaternion rotation
        marker.scale.x = 2*obstacles.Obstacles[obst_it].major_semiaxis;     // Marker is specified by diameter, not radius!
        marker.scale.y = 2*obstacles.Obstacles[obst_it].minor_semiaxis;
        marker.scale.z = 0.01;
        marker.color.a = 1.0;
        marker.color.r = 0.0;
        marker.color.g = 1.0;
        marker.color.b = 0.0;

        markerArray.markers.push_back(marker);
    }


    // Create hardcoded circles to represent ego vehicle discs of mpc controller
    marker.header.frame_id = "base_link";              // Add frame of robot
    marker.header.stamp = ros::Time::now();            // Add timestamp
    marker.id = 91;                                    // Obstacle ID
    marker.type = visualization_msgs::Marker::CYLINDER;
    marker.pose.position.x = -0.0833;   // DEPENDS ON # DISCS
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.scale.x = 2*0.2603;          // DEPENDS ON # DISCS
    marker.scale.y = 2*0.2603;          // Marker is specified by diameter, not radius!
    marker.scale.z = 0.01;
    marker.color.a = 1.0;
    marker.color.r = 0.0;
    marker.color.g = 0.0;
    marker.color.b = 1.0;

    markerArray.markers.push_back(marker);

    marker.header.frame_id = "base_link";               // Add frame of robot
    marker.header.stamp = ros::Time::now();             // Add timestamp
    marker.id = 92;                                     // Obstacle ID
    marker.type = visualization_msgs::Marker::CYLINDER;
    marker.pose.position.x = 0.0833;    // DEPENDS ON # DISCS
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.scale.x = 2*0.2603;          // DEPENDS ON # DISCS
marker.scale.y = 2*0.2603;              // Marker is specified by diameter, not radius!
    marker.scale.z = 0.01;
    marker.color.a = 1.0;
    marker.color.r = 0.0;
    marker.color.g = 0.0;
    marker.color.b = 1.0;

    markerArray.markers.push_back(marker);

    visualize_obstacles_pub.publish(markerArray);
}

void ObstacleFeed::updateObstacles(const ros::TimerEvent& event)
{
    // Create header for obstacles
    std_msgs::Header obst_header;
    obst_header.stamp = ros::Time::now();
    obst_header.frame_id = obstacle_base_link_;

    // Create temporary obstacle entities
    obstacle_feed::Obstacles obstacles;
    obstacle_feed::Obstacle obstacle;

    // Loop over predefined obstacles in yaml file
    for (int obst_it = 0; obst_it < obstacle_feed_config_->obst_pose_x_.size(); obst_it++){

        obstacle.pose.position.x = obstacle_feed_config_->obst_pose_x_.at(obst_it);
        obstacle.pose.position.y = obstacle_feed_config_->obst_pose_y_.at(obst_it);
        obstacle.pose.position.z = 0;
        obstacle.pose.orientation.z = obstacle_feed_config_->obst_pose_heading_.at(obst_it);

        obstacle.minor_semiaxis = obstacle_feed_config_->obst_dim_minor_.at(obst_it);
        obstacle.major_semiaxis = obstacle_feed_config_->obst_dim_major_.at(obst_it);

        obstacles.Obstacles.push_back(obstacle);
    }

    // Publish ellipsoid obstacles
    publishObstacles(obstacles);
    // Visualize ellipsoid obstacles
    visualizeObstacles(obstacles);
}

bool CompareObstacleDistance(obstacle_feed::Obstacle& obst1, obstacle_feed::Obstacle& obst2) { return (obst1.distance < obst2.distance); }

void ObstacleFeed::OrderObstacles(obstacle_feed::Obstacles& ellipses)
{
    // Create vector of obstacles
    std::vector<obstacle_feed::Obstacle> ellipsesVector;
    ellipsesVector = ellipses.Obstacles;

    // Sort vector according to distances
    std::sort(ellipsesVector.begin(), ellipsesVector.end(), CompareObstacleDistance);

    // Write vector of sorted obstacles to obstacles structure
    ellipses.Obstacles = ellipsesVector;

//    // print out content:
//    std::cout << "myvector contains:";
//    for (int it = 0; it < ellipses.Obstacles.size(); it++)
//        std::cout << ' ' << ellipses.Obstacles[it].distance;
//    std::cout << '\n';
}

obstacle_feed::Obstacle ObstacleFeed::FitEllipse(const autoware_msgs::DetectedObject& object, const double& distance)
{
    obstacle_feed::Obstacle ellipse;

    ellipse.major_semiaxis = sqrt(pow(object.dimensions.x,2) + pow(object.dimensions.y,2))/2;
    ellipse.minor_semiaxis = sqrt(pow(object.dimensions.x,2) + pow(object.dimensions.y,2))/2;
    ellipse.distance = distance;
    ellipse.pose = object.pose;
    ellipse.velocity = object.velocity;

    return ellipse;
}

void ObstacleFeed::QuatToZRot(geometry_msgs::Pose& pose)
{
    double ysqr = pose.orientation.y * pose.orientation.y;
    double t3 = +2.0 * (pose.orientation.w * pose.orientation.z + pose.orientation.x * pose.orientation.y);
    double t4 = +1.0 - 2.0 * (ysqr + pose.orientation.z * pose.orientation.z);

    pose.orientation.z = atan2(t3, t4);
}

void ObstacleFeed::ZRotToQuat(geometry_msgs::Pose& pose)
{
    pose.orientation.w = cos(pose.orientation.z * 0.5);
    pose.orientation.x = 0;
    pose.orientation.y = 0;
    pose.orientation.z = sin(pose.orientation.z * 0.5);
}

bool ObstacleFeed::transformPose(const std::string& from, const std::string& to, geometry_msgs::Pose& pose)
{
    bool transform = false;
    tf::StampedTransform stamped_tf;

    geometry_msgs::PoseStamped stampedPose_in, stampedPose_out;

    stampedPose_in.pose = pose;
//    stampedPose_in.header.stamp = ros::Time::now();
    stampedPose_in.header.frame_id = from;

    // make sure source and target frame exist
    if (tf_listener_.frameExists(to) && tf_listener_.frameExists(from))
    {
        try
        {
            // find transforamtion between souce and target frame
            tf_listener_.waitForTransform(from, to, ros::Time(0), ros::Duration(0.02));
            tf_listener_.transformPose(to, stampedPose_in, stampedPose_out);

            transform = true;
        }
        catch (tf::TransformException& ex)
        {
            ROS_ERROR("MPCC::getTransform: %s", ex.what());
        }
    }

    else
    {
        ROS_WARN("MPCC::getTransform: '%s' or '%s' frame doesn't exist, pass existing frame",from.c_str(), to.c_str());
    }

    stampedPose_in.pose = stampedPose_out.pose;
    stampedPose_in.header.frame_id = to;

    return transform;
}

bool ObstacleFeed::getTransform(const std::string& from, const std::string& to, Eigen::VectorXd& stamped_pose)
{
    bool transform = false;
    stamped_pose = Eigen::VectorXd(6);
    tf::StampedTransform stamped_tf;

    // make sure source and target frame exist
    if (tf_listener_.frameExists(to) && tf_listener_.frameExists(from))
    {
        try
        {
            // find transforamtion between souce and target frame
            tf_listener_.waitForTransform(from, to, ros::Time(0), ros::Duration(0.02));
            tf_listener_.lookupTransform(from, to, ros::Time(0), stamped_tf);

            // translation
            stamped_pose(0) = stamped_tf.getOrigin().x();
            stamped_pose(1) = stamped_tf.getOrigin().y();
            stamped_pose(2) = stamped_tf.getOrigin().z();

            // convert quternion to rpy
            tf::Quaternion quat(stamped_tf.getRotation().getX(),
                                                    stamped_tf.getRotation().getY(),
                                                    stamped_tf.getRotation().getZ(),
                                                    stamped_tf.getRotation().getW()
            );

            if (activate_debug_output_)
            {
                std::cout << "\033[94m" << "getTransform:" << " qx:" << stamped_tf.getRotation().getX()
                                    << "qy:" << stamped_tf.getRotation().getY()
                                    << "qz:" << stamped_tf.getRotation().getZ()
                                    << "qw:" << stamped_tf.getRotation().getW() << "\033[0m" <<std::endl;
            }

            tf::Matrix3x3 quat_matrix(quat);
            quat_matrix.getRPY(stamped_pose(3), stamped_pose(4), stamped_pose(5));

            if (activate_debug_output_)
            {
                std::cout << "\033[32m" << "getTransform:" << " roll:" << stamped_pose(3)
                                    << " pitch:" << stamped_pose(4)
                                    << " yaw:" << stamped_pose(5)
                                    << "\033[0m" <<std::endl;
            }

            transform = true;
        }
        catch (tf::TransformException& ex)
        {
            ROS_ERROR("MPCC::getTransform: %s", ex.what());
        }
    }

    else
    {
        ROS_WARN("MPCC::getTransform: '%s' or '%s' frame doesn't exist, pass existing frame",
                         from.c_str(), to.c_str());
    }

    return transform;
}
