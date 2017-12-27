#!/bin/sh
#echo -n "Enter a root path of TohriSDK($PWD) : "     #for Linux
/bin/echo -n "Enter a root path of TohriSDK($PWD) : " #for Mac
read SDK_PATH

if [ "$SDK_PATH"="" ]
then
SDK_PATH=`pwd`
fi

echo "\"$SDK_PATH\" is set."

#echo -n "Enter the build target name : "     #for Linux
/bin/echo -n "Enter the build target name : " #for Mac
read BUILD_TARGET
echo "Builded Objects will be put to \"out/$BUILD_TARGET/\"."

export TOHRI_SDK_PATH=$SDK_PATH
export TOHRI_SDK_BUILD_PATH=$TOHRI_SDK_PATH/build
export TOHRI_SDK_TARGET=$BUILD_TARGET
export TOHRI_SDK_USE=true

