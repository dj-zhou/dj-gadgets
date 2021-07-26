#!/bin/bash
# to make this file excutable: chmod u+x install.sh

echo "djfile - make again"
make
echo "djfile - copy to /usr/bin"
sudo cp djfile /usr/bin
