//
// Created by m3sc4 on 14.05.15.
//

#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <boost/archive/text_iarchive.hpp>
#include <boost/asio.hpp>
#include "server.h"
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <string.h>

template <class PackEntity>
string packToString(const PackEntity& entity) {
    ostringstream serialize_stream;
    boost::archive::text_oarchive serializer(serialize_stream);
    serializer << entity;
    return string(std::move(serialize_stream.str()));
}

template <class UnpackEntity>
UnpackEntity unpackFromString(const string& packed) {
    UnpackEntity entity;
    istringstream serializable_stream(packed);
    boost::archive::text_iarchive in(serializable_stream);
    in >> entity;
    return entity;
}

template <class WriteEntity>
void serializedWrite(SocketImplementation & writeSocket, const WriteEntity& entity) {
    auto packed = packToString(entity);
    writeSocket.writeData(packed.c_str(), strlen(packed.c_str()) * sizeof(char));
}

template <class WriteEntity>
void serializedWrite(boost::asio::ip::tcp::socket& socket, const WriteEntity& entity) {
    auto packed = packToString(entity);
    socket.write_some(boost::asio::buffer(packed.c_str(), strlen(packed.c_str()) * sizeof(char)));
}

template <class ReadEntity>
ReadEntity serializedRead(SocketImplementation & readSocket) {
    char* buffer = new char[256];
    string data;
    ssize_t number_of_bytes_read;
    do {
        memset(buffer, 0, 256);
        number_of_bytes_read = readSocket.readData(buffer, 255);
        data += buffer;
    } while ( number_of_bytes_read == 255 );
    delete[] buffer;
    return unpackFromString<ReadEntity>(data);
}

template <class ReadEntity>
ReadEntity serializedRead(boost::asio::ip::tcp::socket& socket) {
    char* buffer = new char[256];
    string data;
    ssize_t number_of_bytes_read;
    do {
        memset(buffer, 0, 256);
        number_of_bytes_read = socket.read_some(boost::asio::buffer(buffer, 255));
        data += buffer;
    } while ( number_of_bytes_read == 255 );
    delete[] buffer;
    return unpackFromString<ReadEntity>(data);
}

#endif 
