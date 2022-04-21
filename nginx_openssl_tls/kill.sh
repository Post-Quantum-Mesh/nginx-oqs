#!/bin/sh

# Run from CWD using "./kill.sh"

# Kill container
echo "Killing tls container..."
echo
sudo docker kill tls-test-img

# Prune containers
echo "Pruning containers..."
echo
sudo docker container prune -f

# Prune network
echo "Pruning networks..."
echo
sudo docker network prune -f
