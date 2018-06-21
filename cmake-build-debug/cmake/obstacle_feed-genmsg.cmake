# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "obstacle_feed: 2 messages, 0 services")

set(MSG_I_FLAGS "-Iobstacle_feed:/home/boaz/workspace/src/obstacle_feed/msg;-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(obstacle_feed_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/boaz/workspace/src/obstacle_feed/msg/Obstacle.msg" NAME_WE)
add_custom_target(_obstacle_feed_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "obstacle_feed" "/home/boaz/workspace/src/obstacle_feed/msg/Obstacle.msg" "geometry_msgs/Quaternion:geometry_msgs/Vector3:geometry_msgs/Twist:geometry_msgs/Point:geometry_msgs/Pose"
)

get_filename_component(_filename "/home/boaz/workspace/src/obstacle_feed/msg/Obstacles.msg" NAME_WE)
add_custom_target(_obstacle_feed_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "obstacle_feed" "/home/boaz/workspace/src/obstacle_feed/msg/Obstacles.msg" "geometry_msgs/Point:geometry_msgs/Vector3:std_msgs/Header:geometry_msgs/Quaternion:obstacle_feed/Obstacle:geometry_msgs/Pose:geometry_msgs/Twist"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(obstacle_feed
  "/home/boaz/workspace/src/obstacle_feed/msg/Obstacle.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/obstacle_feed
)
_generate_msg_cpp(obstacle_feed
  "/home/boaz/workspace/src/obstacle_feed/msg/Obstacles.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/boaz/workspace/src/obstacle_feed/msg/Obstacle.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Twist.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/obstacle_feed
)

### Generating Services

### Generating Module File
_generate_module_cpp(obstacle_feed
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/obstacle_feed
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(obstacle_feed_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(obstacle_feed_generate_messages obstacle_feed_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/boaz/workspace/src/obstacle_feed/msg/Obstacle.msg" NAME_WE)
add_dependencies(obstacle_feed_generate_messages_cpp _obstacle_feed_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/boaz/workspace/src/obstacle_feed/msg/Obstacles.msg" NAME_WE)
add_dependencies(obstacle_feed_generate_messages_cpp _obstacle_feed_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(obstacle_feed_gencpp)
add_dependencies(obstacle_feed_gencpp obstacle_feed_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS obstacle_feed_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(obstacle_feed
  "/home/boaz/workspace/src/obstacle_feed/msg/Obstacle.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/obstacle_feed
)
_generate_msg_lisp(obstacle_feed
  "/home/boaz/workspace/src/obstacle_feed/msg/Obstacles.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/boaz/workspace/src/obstacle_feed/msg/Obstacle.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Twist.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/obstacle_feed
)

### Generating Services

### Generating Module File
_generate_module_lisp(obstacle_feed
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/obstacle_feed
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(obstacle_feed_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(obstacle_feed_generate_messages obstacle_feed_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/boaz/workspace/src/obstacle_feed/msg/Obstacle.msg" NAME_WE)
add_dependencies(obstacle_feed_generate_messages_lisp _obstacle_feed_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/boaz/workspace/src/obstacle_feed/msg/Obstacles.msg" NAME_WE)
add_dependencies(obstacle_feed_generate_messages_lisp _obstacle_feed_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(obstacle_feed_genlisp)
add_dependencies(obstacle_feed_genlisp obstacle_feed_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS obstacle_feed_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(obstacle_feed
  "/home/boaz/workspace/src/obstacle_feed/msg/Obstacle.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Twist.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/obstacle_feed
)
_generate_msg_py(obstacle_feed
  "/home/boaz/workspace/src/obstacle_feed/msg/Obstacles.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Vector3.msg;/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Quaternion.msg;/home/boaz/workspace/src/obstacle_feed/msg/Obstacle.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Twist.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/obstacle_feed
)

### Generating Services

### Generating Module File
_generate_module_py(obstacle_feed
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/obstacle_feed
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(obstacle_feed_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(obstacle_feed_generate_messages obstacle_feed_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/boaz/workspace/src/obstacle_feed/msg/Obstacle.msg" NAME_WE)
add_dependencies(obstacle_feed_generate_messages_py _obstacle_feed_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/boaz/workspace/src/obstacle_feed/msg/Obstacles.msg" NAME_WE)
add_dependencies(obstacle_feed_generate_messages_py _obstacle_feed_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(obstacle_feed_genpy)
add_dependencies(obstacle_feed_genpy obstacle_feed_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS obstacle_feed_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/obstacle_feed)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/obstacle_feed
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(obstacle_feed_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/obstacle_feed)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/obstacle_feed
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(obstacle_feed_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/obstacle_feed)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/obstacle_feed\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/obstacle_feed
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(obstacle_feed_generate_messages_py geometry_msgs_generate_messages_py)
endif()
