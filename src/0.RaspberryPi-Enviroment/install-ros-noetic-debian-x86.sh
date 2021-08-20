#!/bin/bash
#
#   Author: Spyridakis Christos
#   Creation Date: 11/8/2021
#   Last update: 11/8/2021
#
#   Description:
#       Install ROS (Robot Operating System) - on a Debian based OS
#
#       Instructions based on official Documentation
#       https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html
#
#
#   Extra:


# Setup your sources.list
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'

# Set up your keys
sudo apt install curl # if you haven't already installed curl
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -

# Installation
sudo apt update
sudo apt install ros-noetic-desktop-full    # Desktop-Full Install
# sudo apt install ros-noetic-desktop       # Desktop Install
# sudo apt install ros-noetic-ros-base      # ROS-Base

# Environment setup
[ ${SHELL} = "/usr/bin/zsh" ] && (echo -e "\nsource /opt/ros/noetic/setup.zsh \n" >> ~/.zshrc && source ~/.zshrc)

# Dependencies for building packages
sudo apt install python3-rosdep python3-rosinstall python3-rosinstall-generator python3-wstool build-essential

# Initialize rosdep
sudo apt install python3-rosdep
sudo rosdep init
rosdep update