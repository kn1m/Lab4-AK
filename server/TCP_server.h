//
// Created by m3sc4 on 16.05.15.
//

#ifndef LAB4_AK_TCP_SERVER_H
#define LAB4_AK_TCP_SERVER_H

#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <cstring> // Needed for memset



class TCP_server
{
    private:
        int socket;

    public:
        TCP_server();
        ~TCP_server() = delete;
};


#endif //LAB4_AK_TCP_SERVER_H
