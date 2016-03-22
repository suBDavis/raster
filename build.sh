#!/bin/bash
BEGIN=$(date +"%S")
echo "<<============================================================>>"
echo "    Began compiling at $(date +"%H:%M:%S")"
echo "    Please allow 30-60 seconds for compile"
mkdir -p Build
mkdir -p Images

args=$1
args="all"
FLAGSBEGIN="-g -O0 -Wall -std=c++0x -o"
FLAGSEND="-I. -larmadillo"

if [ "$args" = "all" ]; then

    g++  -c  "./main.cpp" $FLAGSBEGIN ./Build/main.cpp.o $FLAGSEND
    g++  -c  "./Mesh.cpp" $FLAGSBEGIN ./Build/Mesh.cpp.o $FLAGSEND
    g++  -c  "./Triangle.cpp" $FLAGSBEGIN ./Build/Triangle.cpp.o $FLAGSEND
    g++  -c  "./v3.cpp" $FLAGSBEGIN ./Build/v3.cpp.o $FLAGSEND
    g++  -c  "./Phong.cpp" $FLAGSBEGIN ./Build/Phong.cpp.o $FLAGSEND
    g++  -c  "./Room.cpp" $FLAGSBEGIN ./Build/Room.cpp.o $FLAGSEND
    g++  -c  "./Light.cpp" $FLAGSBEGIN ./Build/Light.cpp.o $FLAGSEND
    g++  -c  "./Ray.cpp" $FLAGSBEGIN ./Build/Ray.cpp.o $FLAGSEND
    g++  -c  "./Renderer.cpp" $FLAGSBEGIN ./Build/Renderer.cpp.o $FLAGSEND

fi

g++ -o ./Build/Rasterize ./Build/main.cpp.o ./Build/Mesh.cpp.o ./Build/Triangle.cpp.o ./Build/v3.cpp.o ./Build/Phong.cpp.o ./Build/Room.cpp.o ./Build/Light.cpp.o ./Build/Ray.cpp.o ./Build/Renderer.cpp.o -L. $FLAGSEND

END=$(date +"%S")
TIME=$((END-BEGIN))
echo -e "\e[92m<<============================================================>>"
echo "   Build completed! Time to build: $( echo ${TIME#-} ) seconds"
echo "   If the build was successful, you may run ./run.sh"
echo "   If there were errors, please retry on ubuntu-based linux"
echo "   or make sure you fulfilled the build requirements"
echo -e "<<============================================================>>\e[39m"