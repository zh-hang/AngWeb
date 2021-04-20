#include "serverSocket.h"
#include "config.h"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>

ServerSocket::ServerSocket(const std::string host,const unsigned int port,const int domain_type)
{
    char const*hostStr=host.c_str();
    this->hostAddr.sin_family = domain_type;
    this->hostAddr.sin_addr.s_addr = inet_addr(hostStr);
    this->hostAddr.sin_port = htons(port);
    bzero(&(this->hostAddr.sin_zero),8);
    std::cout<<inet_ntoa(this->hostAddr.sin_addr)<<" "<<std::endl;
    if ((this->serverfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("bind error:");
        std::cout << "socket create fail\n";
        exit(1);
    }
    else
    {
        std::cout << "socket create success\n";
    }
    
    // const int on=1;
    // setsockopt(this->serverfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
}

ServerSocket::~ServerSocket()
{
}

void ServerSocket::run()
{
    if (bind(this->serverfd, (struct sockaddr *)&this->hostAddr, sizeof(struct sockaddr)) != 0)
    {
        std::cout << "socket bind fail\n";
        exit(1);
    }
    if (listen(this->serverfd, MAX_LISTEN_NUM) < 0)
    {
        std::cout << "close listen\n";
        exit(1);
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