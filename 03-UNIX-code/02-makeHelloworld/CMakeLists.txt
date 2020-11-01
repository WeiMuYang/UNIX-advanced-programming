cmake_minimum_required(VERSION 2.8)
project(helloworld)
SET(CMAKE_BUILD_TYPE Release)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
include_directories(
${PROJECT_SOURCE_DIR}/include
)

add_executable(helloworld src/helloworld.cpp src/main.cpp)

