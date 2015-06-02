cmake_minimum_required(VERSION 3.2)
project(Lab4_AK)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread -lboost_serialization -lboost_program_options -lboost_system")

set(SOURCE_FILES core.cpp)
add_executable(ComputerArchitecture4 ${SOURCE_FILES} server_implementation/thread_implementation.h server_implementation/thread_implementation.cpp server_implementation/server.cpp server_implementation/server.h server_implementation/templates.h server_implementation/asio_server.h server_implementation/dijkstra_algo.h)
