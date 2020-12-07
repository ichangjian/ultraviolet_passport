cmake_minimum_required (VERSION 2.8.9)

add_library(lib_truefalse SHARED IMPORTED)
set_target_properties(lib_truefalse PROPERTIES IMPORTED_LOCATION 
${CMAKE_HOME_DIRECTORY}/../build_android/libtruefalse.so)

add_library( native-truefalse SHARED com_truefalse_sdk_upTrueFalse.cpp)

target_link_libraries(native-truefalse lib_truefalse log)