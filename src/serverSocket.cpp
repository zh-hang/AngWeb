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
    char const*hostStr=this->host.configData["host"].c_str();
    std::cout<<hostStr<<std::endl;
    this->hostAddr.sin_family = this->host.getDomain();
    this->hostAddr.sin_addr.s_addr = inet_addr(hostStr);
    this->hostAddr.sin_port = std::stoi(this->host.configData["port"]);
    std::cout<<this->hostAddr.sin_port<<" "<<this->hostAddr.sin_addr.s_addr<<std::endl;
    if ((this->serverfd = socket(this->host.getDomain(), SOCK_STREAM, 0)) == -1)
    {
        perror("bind error:");
        std::cout << "socket create fail\n";
        exit(1);
    }
    else
    {
        std::cout << "socket create success\n";
    }
    
    const int on=1;
    setsockopt(this->serverfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
}

ServerSocket::~ServerSocket()
{
}

void ServerSocket::run()
{
    if (bind(this->serverfd, (struct sockaddr *)&this->hostAddr, sizeof(this->hostAddr)) != 0)
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