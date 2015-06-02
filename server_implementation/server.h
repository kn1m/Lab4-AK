//
// Created by m3sc4 on 15.05.15.
//

#ifndef SERVER_H
#define SERVER_H

#include <exception>
#include <string>
#include <memory>

using namespace std;

class SocketImplementation {
    public:
        SocketImplementation(int descriptor) : socket_descriptor(descriptor) {}
        SocketImplementation(const SocketImplementation &) = delete;
        SocketImplementation & operator=(const SocketImplementation &) = delete;
        virtual ~SocketImplementation();
        void writeData(const void *data, size_t size);
        ssize_t readData(void *buffer, size_t size);
    protected:
        int getDescriptor();
        SocketImplementation();
    private:
        int socket_descriptor;
};

class IncomingData : public SocketImplementation {
    public:
        IncomingData(unsigned short port, int backlog = 10);
        unique_ptr<SocketImplementation> accept_connection();
    private:
        unsigned short port;
};


class ConnectionError : public exception {
    public:
        ConnectionError(string msg = string("Something wrong with tcp socket."), int error_number=-1)
                : error_number(error_number), msg(msg) {}
        virtual const char *what() const noexcept (true) override;
        const int error_number;
    private:
        string msg;
};

class OutcomingData : public SocketImplementation {
    public:
        OutcomingData(string host, unsigned short port);
        unsigned short getPort() const {
            return port;
        }
        string getHost() const {
            return host;
        }
    private:
        string host;
        unsigned short port;
};

#endif
