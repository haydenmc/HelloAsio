cmake_minimum_required(VERSION 3.20)

project(HelloAsio)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Sub-projects
add_subdirectory ("src/Server")