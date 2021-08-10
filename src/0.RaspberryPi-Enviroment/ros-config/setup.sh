#!/bin/bash

CONFIGS_SUB_DIR=.conf
mkdir -p ${CONFIGS_SUB_DIR}

# For remote developmen configuration
if [ ! -f ./${CONFIGS_SUB_DIR}/ros_remote.conf ] ; then
    echo "Create ros_remote.conf file"
    echo -e 'ROS_HOSTNAME= \nROS_IP= \nROS_MASTER_URI=http://todo:11311/' > ./${CONFIGS_SUB_DIR}/ros_remote.conf
fi 

# Default workspace location
if [ ! -f ./${CONFIGS_SUB_DIR}/catkin_ws_location ] ; then
    echo "Create catkin_ws_location file"
    echo $HOME > ./${CONFIGS_SUB_DIR}/catkin_ws_location
fi 

# Default workspace name
if [ ! -f ./${CONFIGS_SUB_DIR}/catkin_ws_name ] ; then
    echo "Create catkin_ws_name file"
    echo catkin_ws > ./${CONFIGS_SUB_DIR}/catkin_ws_name
fi 

# Source ROS' default workspace
if [ `cat ~/.zshrc | grep /opt/ros/${ROS_DISTRO}/setup.zsh | wc -l` -eq 0 ] ; then
    echo "Add Ros default workspace to ~/.zshrc"
    echo "source /opt/ros/${ROS_DISTRO}/setup.zsh # Ros default workspace" >> ~/.zshrc
fi 

# Source user defined file
if [ `cat ~/.zshrc | grep ros-zshrc.zsh | wc -l` -eq 0 ] ; then
    echo "Add User macros and env variables file to ~/.zshrc"
    echo "source ${PWD}/ros-zshrc.zsh # User defined macros and env variables" >> ~/.zshrc
fi 

# Then source ~/.zshrc