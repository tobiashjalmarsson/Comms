cmake_minimum_required(VERSION 3.26)
project(Comms)

set(CMAKE_CXX_STANDARD 17)

add_executable(Comms main.cpp
        server.cpp
        server.h
        client.cpp
        client.h
        helpers.cpp
        helpers.h
)
