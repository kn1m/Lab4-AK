//
// Created by m3sc4 on 15.05.15.
//


#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>

int SocketImplementation::getDescriptor() {
    return socket_descriptor;
}

SocketImplementation::SocketImplementation() {
    socket_descriptor = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_descriptor < 0) {
        throw ConnectionError("TCP socket can't be opened.", errno);
    }
}


void SocketImplementation::writeData(const void *data, size_t size) {
    if ( write(socket_descriptor, data, size) < 0 ) {
        throw ConnectionError("Write error.", errno);
    }
}

ssize_t SocketImplementation::readData(void *buffer, size_t size) {
    ssize_t byte_read = read(socket_descriptor, buffer, size);
    if ( byte_read < 0) {
        throw ConnectionError("Read error.", errno);
    }
    return byte_read;
}


SocketImplementation::~SocketImplementation() {
    close(socket_descriptor);
}

IncomingData::IncomingData(unsigned short port, int backlog) : SocketImplementation(), port(port) {

    sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = PF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);
    if ( bind(getDescriptor(), (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        throw ConnectionError("Bind error.", errno);
    }
    listen(getDescriptor(), backlog);
}

unique_ptr<SocketImplementation> IncomingData::accept_connection() {
    sockaddr_in client_address;
    socklen_t client_len = sizeof(client_address);
    int new_socket_descriptor = accept(getDescriptor(),
                                       (struct sockaddr *) &client_address,
                                       &client_len);
    if (new_socket_descriptor < 0) {
        throw ConnectionError("Accept error.", errno);
    }
    unique_ptr<SocketImplementation> new_socket_ptr(new SocketImplementation(new_socket_descriptor));
    return new_socket_ptr;
}

const char*ConnectionError::what() const noexcept (true) {
    return this->msg.c_str();
}

OutcomingData::OutcomingData(string host, unsigned short port) : host(host), port(port){
    hostent *server = gethostbyname(host.c_str());
    if ( server == nullptr) {
        throw ConnectionError("Host not found.", errno);
    }
    sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    bcopy(server->h_addr,
          (char *)&server_address.sin_addr.s_addr,
          (size_t)server->h_length);
    if ( connect(getDescriptor(),(struct sockaddr *) &server_address, sizeof(server_address) ) < 0) {
        throw ConnectionError("Connect error", errno);
    }

}
