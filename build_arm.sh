#!/bin/sh

export PATH="/opt/onyx/arm/bin:/opt/freescale/usr/local/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/:$PATH"
export ONYX_SDK_ROOT=/opt/onyx/arm
export PKG_CONFIG_PATH=/opt/onyx/arm/lib/pkgconfig/
export QMAKESPEC=/opt/onyx/arm/mkspecs/qws/linux-arm-g++/

qmake ssh_server.pro DEFINES+=BUILD_FOR_ARM
make
arm-linux-strip ssh_server
