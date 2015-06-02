
#define DEFAULT_PORT 8000


#include <iostream>
#include <boost/serialization/vector.hpp>
#include <boost/program_options.hpp>
#include "server_implementation/templates.h"
#include "server_implementation/dijkstra_algo.h"
#include "server_implementation/server.h"
#include "server_implementation/thread_implementation.h"
#include "server_implementation/asio_server.h"

using namespace threading;
using namespace std;
using namespace boost::program_options;

template <class Socket>
void handleRequest(Socket &socket) {
    vector<vector<int>> graph_data = serializedRead< vector<vector<int>> >(socket);
    auto Dijkstra_A = DijkstraAlgo(graph_data, 0);
    auto Result = Dijkstra_A.Dijkstra(Dijkstra_A.Graph, Dijkstra_A.vertex);
    serializedWrite(socket, Result);
}

int main(int argc, char *argv[]) {
    unsigned short port;
    int THREADING_FORK = 1;
    int THREADING_PTHREAD = 2;
    int ASIO_ASYNC = 3;
    int SERVER_MODEL = ASIO_ASYNC;
    options_description desc("Client options");
    desc.add_options()
            ("help,h", "produce help message")
            ("port,p", value<unsigned short>(&port)->default_value(DEFAULT_PORT), "server_implementation port");
    variables_map args;
    try {
        parsed_options parsed = command_line_parser(argc, argv).options(desc).run();
        store(parsed, args);
        notify(args);
    } catch(std::exception& ex) {
        cerr << desc << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Server listening at port " << port << "..." << endl;
    if(SERVER_MODEL == THREADING_FORK || SERVER_MODEL == THREADING_PTHREAD) {
        IncomingData server_socket(port);

        while (true) {
            auto new_socket = server_socket.accept_connection();

            if(SERVER_MODEL == THREADING_FORK)
            {
                if (!fork()) {
                    handleRequest(*new_socket.get());
                    break;
                }
            }
            if(SERVER_MODEL == THREADING_PTHREAD) {
                auto socket_ptr = new unique_ptr<SocketImplementation>(std::move(new_socket));
                Thread task_thread([](void *socket) -> void * {
                    unique_ptr<SocketImplementation> *data_socket = (unique_ptr<SocketImplementation> *) socket;
                    handleRequest(*(*data_socket).get());
                    delete data_socket;
                    return nullptr;
                }, socket_ptr);
                task_thread.deatch();
            }
        }
    }
    if (SERVER_MODEL == ASIO_ASYNC)
    {
        AsioTCP::TCPServer server(port, [] (AsioTCP::TCPServer::socket_ptr socket)->void {
            handleRequest(*socket);
        });
        server.run();
    }


    return 0;
}
