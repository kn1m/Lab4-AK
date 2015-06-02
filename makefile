#
# Created by Pete K. 16.05.15.
#

source_files ?= server_implementation/thread_implementation.cpp server_implementation/server.cpp
headers ?= server_implementation/thread_implementation.h server_implementation/server.h server_implementation/templates.h server_implementation/asio_server.h server_implementation/dijkstra_algo.h
flags += -lpthread -std=c++11 -lboost_serialization -lboost_program_options -lboost_system
warnings ?= -Wall -Wextra -Wsign-compare -Wunused-parameter -Wunused-variable
main_file ?= core.cpp

all : run

run : server_runnable
	./server_runnable -p 8000

server_runnable : .build
	g++ .build/* -o server_runnable $(flags)

.build : $(headers) $(source_files) core.cpp
	if ! [ -d .build ]; then mkdir .build; fi
	rm -rf .build/*
	( cd .build ; g++ $(addprefix ../, core.cpp  $(source_files)) -c $(flags) $(additional_flags) $(warnings))

clean :
	rm -rf .build
	rm -rf server_runnable
	( cd tests; rm -rf tests )

unittest : runnable

runnable : tests/tests
	( cd tests; ./tests )

tests/tests : $(shell find tests -name "*.cpp")
	( cd tests; g++ $(addprefix ../, $(source_files) $(shell find tests -name "*.cpp"))  $(flags) $(additional_flags) -lboost_unit_test_framework -o tests)