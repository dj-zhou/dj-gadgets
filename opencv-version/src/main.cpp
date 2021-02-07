/******************************************************************************
File Name     : main.cpp
Author        : Dingjiang Zhou
Email         : zhoudingjiang@gmail.com
Create Time   : Sat, Feb. 06th, 2021. 06:49:17 PM
Last Modified :
Purpose       :
-------------------------------------------------------------------------------
INPUTS

OUTPUTS

******************************************************************************/

#include <opencv2/core/version.hpp>

#include <stdio.h>

using namespace std;

int main(int argc, char* argv[]) {
    ( void )argc;
    ( void )argv;
    printf("%d.%d.%d\r\n", CV_VERSION_MAJOR, CV_VERSION_MINOR,
           CV_VERSION_REVISION);
    return 0;
}
