cmake_minimum_required(VERSION 3.2)
project(Lab4_AK)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES core.cpp)
add_executable(Lab4_AK ${SOURCE_FILES} server/TCP_server.cpp server/TCP_server.h) # client/client.cpp)