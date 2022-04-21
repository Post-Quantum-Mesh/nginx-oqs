#!/bin/sh

# Run from CWD using "./init.sh"

# Build image
sudo docker build -t tls-test-img .

# Create network
sudo docker network create test_net

# Run container
sudo docker run --network test_net --name tls-test-img -p 4433:4433 tls-test-img
