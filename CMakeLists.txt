cmake_minimum_required(VERSION 3.5)
project(slamlearn)
# opencv
set(CMAKE_CXX_FLAGS "-std=c++11")
find_package(OpenCV 2.4.13 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} src/readfile.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})