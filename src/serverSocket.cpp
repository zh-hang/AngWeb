#include "serverSocket.h"
#include "config.h"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>

ServerSocket::ServerSocket(config host)
{
    this->host = host;
    char *hostStr;
    hostStr = new char[this->host.configData["host"].length()];
    std::copy(this->host.configData["host"].begin(), this->host.configData["host"].end(), hostStr);
    std::cout << hostStr << std::endl;
    this->hostAddr.sin_family = this->host.getDomain();
    this->hostAddr.sin_addr.s_addr = inet_addr(hostStr);
    this->hostAddr.sin_port = htons(std::stoi(this->host.configData["port"]));
    std::cout<<this->hostAddr.sin_port<<" "<<this->hostAddr.sin_addr.s_addr<<std::endl;
    if ((this->serverfd = socket(this->host.getDomain(), SOCK_STREAM, 0)) == -1)
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
    if (bind(this->serverfd, (struct sockaddr *)&this->hostAddr, sizeof(sockaddr)) != 0)
    {
        std::cout << "socket bind fail\n";
        exit(1);
    }
    if (listen(this->serverfd, MAX_LISTEN_NUM) < 0)
    {
        std::cout << "close listen\n";
        return;
    }
    std::cout<<"listening...\n";
    while (1)
    {
        socklen_t clientLen = sizeof(struct sockaddr_storage);
        sockaddr *clientAddr;
        int connfd = accept(this->serverfd, clientAddr, &clientLen);
        std::cout << clientAddr->sa_data << std::endl;
    }
}