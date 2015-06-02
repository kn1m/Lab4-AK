//
// Created by m3sc4 on 15.05.15.
//


#include "../server_implementation/server.h"
#include "../server_implementation/templates.h"
#include <boost/serialization/vector.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <random>
#include <chrono>
#include <stdio.h>

#define DEFAULT_PORT 8000
#define DEFAULT_HOST "localhost"

using namespace std;
using namespace boost::program_options;

int main(int argc, char *argv[]) {
    string hostname;
    unsigned short port;
    int request_length;
    double a, b;

    options_description desc("Client options");
    desc.add_options()
            ("help,h", "help")
            ("port,p", value<unsigned short>(&port)->default_value(DEFAULT_PORT), "set port")
            ("location,l", value<string>(&hostname)->default_value(DEFAULT_HOST), "set host")
            ("size,s", value<int>(&request_length)->required(), "set graph size");
    variables_map args;

    try {
        parsed_options parsed = command_line_parser(argc, argv).options(desc).run();
        store(parsed, args);
        notify(args);
    } catch(std::exception& ex) {
        cerr << desc << endl;
        exit(EXIT_FAILURE);
    }


    vector<vector<int>> vector_to_sort{{0, 4, 0, 0, 0, 0, 0, 8, 0},
                       {4, 0, 8, 0, 0, 0, 0, 11, 0},
                       {0, 8, 0, 7, 0, 4, 0, 0, 2},
                       {0, 0, 7, 0, 9, 14, 0, 0, 0},
                       {0, 0, 0, 9, 0, 10, 0, 0, 0},
                       {0, 0, 4, 0, 10, 0, 2, 0, 0},
                       {0, 0, 0, 14, 0, 2, 0, 1, 6},
                       {8, 11, 0, 0, 0, 0, 1, 0, 7},
                       {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };

    OutcomingData out(hostname, port);

    serializedWrite(out, vector_to_sort);

    vector<int> result = serializedRead<vector<int>>(out);

    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < result.size(); i++)
        printf("%d \t\t %d\n", i, result[i]);


    return 0;
}
