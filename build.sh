#!/bin/bash

Build_Dir="build"

GLFW_Lib="libs/_lin/glfw/lib-64"



#GLFW check
if [ -z "$(ls -A $GLFW_Lib)" ]; then
    echo "ERROR: You must build GLFW from sources, and put lib files into [$GLFW_Lib]"
fi


#build
#{

#make build dir
if ! [ -d "$Build_Dir" ]; then
    echo "Create build directory..."
    mkdir "$Build_Dir"
fi

cd $Build_Dir
cmake ..

read

#}
