project( GrabImage )
cmake_minimum_required(VERSION 2.8)
find_package( OpenCV REQUIRED )
add_executable( GrabImage grabimage.cpp )
target_link_libraries( GrabImage ${OpenCV_LIBS} )
