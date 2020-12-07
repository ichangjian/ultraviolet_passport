cmake_minimum_required (VERSION 2.8.9)

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})   
add_library( native-truefalse SHARED com_truefalse_sdk_upTrueFalse.cpp ../truefalse.cpp)

target_link_libraries(native-truefalse  log jnigraphics ${OpenCV_LIBRARIES})