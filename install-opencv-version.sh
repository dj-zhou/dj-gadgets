#!/bin/bash
if [[ -f "/usr/local/lib/libopencv_core.so" ]] ; then
    cd opencv-version
    sudo make install
    cd ..
fi
