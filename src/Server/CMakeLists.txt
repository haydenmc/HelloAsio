# CMakeList.txt : CMake project for TelnetBlackjack, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# ASIO dependency
include(../../cmake/dependencies/asio.cmake)

# Add source to this project's executable.
add_executable (Server "main.cpp")
target_link_libraries(Server asio)

# TODO: Add tests and install targets if needed.
