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

__INST speedtest-cli 
__INST htop 
__INST psensor 
__INST tree 
__INST hardinfo 
__INST ncdu 
__INST ranger 
__INST screenfetch 
__INST python3-pip

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