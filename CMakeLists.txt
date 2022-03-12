# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("TelnetBlackjack")

# Specify C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add dependencies
include(cmake/CPM.cmake)

# Include sub-projects.
add_subdirectory ("src/Server")
