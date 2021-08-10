#!/bin/bash
SESSION="Thesis"

# Create session
tmux -2 new-session -d -s $SESSION

# Create panes
tmux split-window -h
tmux select-pane -t 0
tmux split-window -v
tmux split-window -v
tmux select-pane -t 3
tmux split-window -v
tmux select-pane -t 3
tmux split-window -h
tmux select-pane -t 5
tmux split-window -v
tmux split-window -h

# ----------------------------------------
# Actions

# 0
tmux select-pane -t 0
tmux resize-pane -L 50
tmux send-keys 'clear && ros_develop && rnt'

# 1
tmux select-pane -t 1
tmux send-keys 'roscore' C-m

# 3
tmux select-pane -t 3
tmux send-keys 'watch -n 1 sensors' C-m

# 4
tmux select-pane -t 4
tmux send-keys 'htop' C-m


# Select default window
tmux select-window -t $SESSION

# Attach session to terminal
tmux -2 attach-session -t $SESSION

