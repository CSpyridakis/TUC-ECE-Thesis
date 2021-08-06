#!/bin/bash
SESSION="Thesis"

# Create session
tmux -2 new-session -d -s $SESSION

# Create panes
tmux split-window -v
tmux select-pane -t 0
tmux split-window -h

# Set pane 0 for temperature
tmux select-pane -t 0
tmux resize-pane -L 80
tmux send-keys 'watch -n1 sensors' C-m

# Set pane 1 for cpu usage
tmux select-pane -t 1
tmux resize-pane -U 10
tmux send-keys 'htop' C-m

tmux select-pane -t 2

# Select default window
tmux select-window -t $SESSION

# Attach session to terminal
tmux -2 attach-session -t $SESSION