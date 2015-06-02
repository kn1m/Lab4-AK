#
# Created by m3sc4 on 15.05.15.
#

executable_name ?= client
headers = ../server_implementation/server.h ../server_implementation/templates.h
source_files = client.cpp ../server_implementation/server.cpp
warnings ?= -Wall -Wextra -Wsign-compare -Wunused-parameter -Wunused-variable
flags += -lpthread -std=c++11 -lboost_serialization -lboost_program_options -lboost_system
main_file = client.cpp
run_args = -s 25

all : run

run : executable
	./client $(run_args)

executable : .build
	g++ .build/* -o $(executable_name) $(flags)

.build : $(headers) $(source_files) $(main_file)
	if ! [ -d .build ]; then mkdir .build; fi
	rm -rf .build/*
	( cd .build ; g++ $(addprefix ../, $(main_file)  $(source_files)) -c $(flags) $(additional_flags) $(warnings))

clean :
	rm -rf .build
	rm -rf client