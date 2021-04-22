#include "serverSocket.h"
#include "config.h"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>

ServerSocket::ServerSocket(char const* host_str,const unsigned int port,const int domain_type)
{
    this->host_addr.sin_family = domain_type;
    this->host_addr.sin_addr.s_addr = inet_addr(host_str);
    this->host_addr.sin_port = htons(port);
    bzero(&(this->host_addr.sin_zero),8);
    std::cout<<inet_ntoa(this->host_addr.sin_addr)<<" "<<std::endl;
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
}

ServerSocket::~ServerSocket()
{
}

void ServerSocket::run()
{
    if (bind(this->serverfd, (struct sockaddr *)&this->host_addr, sizeof(struct sockaddr)) != 0)
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
        socklen_t client_len = sizeof(struct sockaddr_storage);
        sockaddr *client_addr;
        int connfd = accept(this->serverfd, client_addr, &client_len);
        std::cout << client_addr->sa_data << std::endl;
    }
}


ServerSocket6::ServerSocket6(char const* host_str, const unsigned int port, const int domain_type)
{
    this.
}

ServerSocket6::~ServerSocket6()
{
}