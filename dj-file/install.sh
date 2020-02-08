#!/bin/bash
# to make this file excutable: chmod u+x install.sh
clear
echo "Make again"
make
echo "Copy to /usr/sbin"
sudo cp djfile /usr/sbin

