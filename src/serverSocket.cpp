#include "serverSocket.h"
#include "config.h"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

ServerSocket::ServerSocket(config host)
{
    this->host = host;
    char *hostStr = new char[this->host.getHost().length()];
    std::copy(this->host.getHost().begin(), this->host.getHost().end(), hostStr);
    if (this->hostInfo == nullptr)
    {
        std::cout << "no address worked\n";
        exit(1);
    }

    getaddrinfo(hostStr, "http", NULL, &this->hostInfo);
    if ((this->serverfd = socket(this->hostInfo->ai_family, SOCK_STREAM, 0)) == -1)
    {
        std::cout << "socket create fail\n";
        exit(1);
    }
    else
    {
        std::cout << "socket create success\n";
    }
}

ServerSocket::~ServerSocket()
{
}

void ServerSocket::run()
{
    if (bind(this->serverfd, this->hostInfo->ai_addr, this->hostInfo->ai_addrlen) != 0)
    {
        std::cout << "socket bind fail\n";
        exit(1);
    }
    if (listen(this->serverfd, MAX_LISTEN_NUM) < 0)
    {
        std::cout << "close listen\n";
        return;
    }
    while (1)
    {
        socklen_t clientLen = sizeof(struct sockaddr_storage);
        sockaddr *clientAddr;
        int connfd = accept(this->serverfd, clientAddr, &clientLen);
        std::cout<<clientAddr->sa_data<<std::endl;
    }
}