mkdir -p Build
mkdir -p Images
FLAGSBEGIN="-g -O3 -Wall -larmadillo -std=c++0x -o"
FLAGSEND="-I."
g++  -c  "./main.cpp" $FLAGSBEGIN ./Build/main.cpp.o -I. -I.
g++  -c  "./Mesh.cpp" $FLAGSBEGIN ./Build/Mesh.cpp.o -I. -I.
g++  -c  "./Triangle.cpp" $FLAGSBEGIN ./Build/Triangle.cpp.o -I. -I.
g++  -c  "./v3.cpp" $FLAGSBEGIN ./Build/v3.cpp.o -I. -I.
g++  -c  "./Phong.cpp" $FLAGSBEGIN ./Build/Phong.cpp.o -I. -I.
g++  -c  "./Room.cpp" $FLAGSBEGIN ./Build/Room.cpp.o -I. -I.
g++  -c  "./Light.cpp" $FLAGSBEGIN ./Build/Light.cpp.o -I. -I.
g++  -c  "./Ray.cpp" $FLAGSBEGIN ./Build/Ray.cpp.o -I. -I.
g++  -c  "./Renderer.cpp" $FLAGSBEGIN ./Build/Renderer.cpp.o -I. -I.
g++ -o ./Build/Rasterize ./Build/main.cpp.o ./Build/Mesh.cpp.o ./Build/Triangle.cpp.o ./Build/v3.cpp.o ./Build/Phong.cpp.o ./Build/Room.cpp.o ./Build/Light.cpp.o ./Build/Ray.cpp.o ./Build/Renderer.cpp.o -L. -larmadillo

echo "<<============================================================>>"
echo "   Build completed"
echo "   If the build was successful, you may run ./run.sh"
echo "   If there were errors, please retry on ubuntu-based linux"
echo "<<============================================================>>"