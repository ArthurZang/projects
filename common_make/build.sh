#!/bin/bash

if [ $# != 2 ]
then
    echo "build.sh target"
    echo "targe can be all,uboot,kernel,program,rootfs,clean"
fi

TARGET=$1

export CROSS_COMPILE= 

export AS=${CROSS_COMPILE}as
export LD=${CROSS_COMPILE}ld
export CC=${CROSS_COMPILE}gcc
export LINK=${CROSS_COMPILE}gcc
export AR=${CROSS_COMPILE}ar
export NM=${CROSS_COMPILE}nm

export TOP_DIR=`pwd`
export PROGRAM_DIR=${TOP_DIR}/program
export BUILD_DIR=${PROGRAM_DIR}/build
export INC_DIR=${TOP_DIR}/include
export LIB_DIR=${TOP_DIR}/lib

export LOG_FILE=${TOP_DIR}/build_log.txt
rm -f ${LOG_FILE}

echo "Start Build" | tee ${LOG_FILE}
date | tee -a ${LOG_FILE}
echo "TARGET=${TARGET}" | tee -a ${LOG_FILE}

if [ ${TARGET} == "all" ];then
    echo "Building uboot"
    echo "Building kernel"
    echo "Building source"
    echo "Building rootfs"
    echo "Building package"
elif [ ${TARGET} == "uboot" ];then
    echo "Building uboot"
elif [ ${TARGET} == "program" ]; then
    echo "Building program"
    make -C program 
elif [ ${TARGET} == "clean" ];then
    echo "Clean"
else
    echo "Error target:${TARGET}"
fi
