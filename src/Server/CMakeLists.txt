cmake_minimum_required (VERSION 3.20)

# Find dependencies
find_package(asio CONFIG REQUIRED)

set(headers
    pch.h
    Listener.h
    Room.h
    ClientConnection.h
)

set(sources
    main.cpp
    Listener.cpp
    Room.cpp
    ClientConnection.cpp
)

# Add source to this project's executable.
add_executable (Server ${sources} ${headers})

# Precompiled header
target_precompile_headers(Server PRIVATE "pch.h")

# Link dependencies
target_link_libraries(Server PRIVATE asio asio::asio)