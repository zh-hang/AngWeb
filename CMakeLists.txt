cmake_minimum_required(VERSION 3.10)

# project version
project(AndWeb VERSION 1.0)

# C++ standard
set(CMAKE_CXX_STANDARD 11) 


# include file directories
#include_directories(${PROJECT_SOURCE_DIR}/src)

# add the executable
add_executable(server ang.cpp)


# include file path
add_subdirectory(src)
target_link_libraries(server PUBLIC LIB)
target_include_directories(server PUBLIC "${PROJECT_BINARY_DIR}"  "${PROJECT_SOURCE_DIR/src}")