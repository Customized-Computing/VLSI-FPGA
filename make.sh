
cd build
cmake ..
make CMAKE_PARAMS="-DVTR_IPO_BUILD=off" -j12 vpr
cd ..