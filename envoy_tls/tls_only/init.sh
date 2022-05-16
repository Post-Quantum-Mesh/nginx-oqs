#!/bin/sh

# Run from CWD using "./init.sh"


echo "Initializing..."
echo
sudo docker-compose pull
sudo docker-compose up --build -d
sudo docker-compose ps
