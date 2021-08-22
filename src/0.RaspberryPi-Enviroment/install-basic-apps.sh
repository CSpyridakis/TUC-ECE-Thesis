#!/bin/bash
#
#   Author: Spyridakis Christos
#   Creation Date: 14/8/2021
#   Last update: 14/8/2021
#
#   Description:
#       Install basic apps in raspberry pi
#

__INST(){
    for app in "$@" 
    do 
        sudo apt-get -y install ${app} 
    done
}

__ADDREP(){
    sudo add-apt-repository -y ${1}
    sudo apt-get -y update --fix-missing
}


sudo apt-get -y update && sudo apt-get -y upgrade

# ----------------------------------------------------------------------------------------------------------------

__INST speedtest-cli 
__INST htop 
__INST psensor 
__INST tree 
__INST hardinfo 
__INST ncdu 
__INST ranger 
__INST screenfetch 
__INST python3-pip
__INST dc

# ZSH
__INST zsh 
__INST fonts-powerline 
sh -c "$(wget https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh -O -)"
chsh -s $(which zsh)

#Neofetch
__ADDREP ppa:dawidd0811/neofetch
__INST neofetch

# Tmux
__INST tmux
__INST xclip


# --------------------------------------------------------------------------------------------------

# For I2C error in ros-adafruit-10dof-library
sudo apt get install libi2c-dev 
# -----------------------------------------------------------------------------------
# * Add #include <sys/ioctl.h>
#
# * Then replace on I2CBuss.cpp line containing #include <linux/i2c-dev.h> with ->
#       extern "C" {
#           include <linux/i2c.h>
#           include <linux/i2c-dev.h>
#           include <i2c/smbus.h>
#       }
# -----------------------------------------------------------------------------------


# TODO: edit them
WIFI_SSID=""
WIFI_PASS=""

# Connect to wifi
nmcli device wifi connect ${WIFI_SSID} password ${WIFI_PASS}

# Disable gui on boot
sudo systemctl set-default multi-user
gnome-session-quit

# Disable suspend
sudo systemctl mask sleep.target suspend.target hibernate.target hybrid-sleep.target

# --------------------------------------------------------------------------------------------------
# Extra ROS packages
__INST ros-noetic-nmea-navsat-driver    # For UART GPS
__INST ros-noetic-robot-localization    # For tf and EKF

__INST ros-noetic-usb-cam               # For USB camera
__INST ros-noetic-opencv                # For image processing
__INST ros-noetic-cv-bridge             # ROS < -- > OpenCV transports (need to include image_transport/image_transport.h & cv_bridge/cv_bridge.h)


# Raspberry Pi serial port is: /dev/ttyS0
# Raspberry Pi bluetooth is: /dev/ttyAMA0
