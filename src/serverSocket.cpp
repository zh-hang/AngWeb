#include "serverSocket.h"
#include "config.h"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>

ServerSocket::ServerSocket(char const *host_str, const unsigned int port)
{
    this->serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->serverfd == -1)
    {
        std::cout << "socket create fail\n";
        exit(-1);
    }
    std::cout << "socket create success\n";

    this->host_addr.sin_family = AF_INET;
    this->host_addr.sin_addr.s_addr = inet_addr(host_str);
    this->host_addr.sin_port = htons(port);
    bzero(&(this->host_addr.sin_zero), 8);
    std::cout << inet_ntoa(this->host_addr.sin_addr) << " " << std::endl;
}

ServerSocket::~ServerSocket()
{
}

void ServerSocket::run()
{
    if (bind(this->serverfd, (struct sockaddr *)&this->host_addr, sizeof(struct sockaddr)) != 0)
    {
        std::cout << "socket bind fail\n";
        exit(-1);
    }
    if (listen(this->serverfd, MAX_LISTEN_NUM) < 0)
    {
        std::cout << "listen fail\n";
        exit(-1);
    }
    std::cout << "listening...\n";
    while (1)
    {
        socklen_t client_len = sizeof(struct sockaddr_storage);
        sockaddr *client_addr;
        int connfd = accept(this->serverfd, client_addr, &client_len);
        std::cout << client_addr->sa_data << std::endl;
    }
}

ServerSocket6::ServerSocket6(char const *host_str, const unsigned int port)
{
    this->serverfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (this->serverfd == -1)
    {
        std::cout << "socket create fail\n";
        exit(-1);
    }
    std::cout << "socket create success\n";
    this->host_addr.sin6_family=AF_INET6;
    this->host_addr.sin6_port=htons(port);
    inet_pton(AF_INET6, host_str, &(this->host_addr.sin6_addr));
    char *str;
    std::cout << inet_ntop(AF_INET6,&(this->host_addr.sin6_addr),str,sizeof(this->host_addr.sin6_addr)) << " " << std::endl;
}

ServerSocket6::~ServerSocket6()
{
}

void ServerSocket6::run(){
    if(bind(this->serverfd,(sockaddr*)&this->host_addr,sizeof(sockaddr_in6)==_1)){
        std::cout<<"socket bind fail\n";
        exit(-1);
    }
    if(listen(this->serverfd,MAX_LISTEN_NUM)<0){
        std::cout<<"listen fail\n";
        exit(-1);
    }
    std::cout<<"listen...\n";
    while (1)
    {
        socklen_t client_len = sizeof(struct sockaddr_storage);
        sockaddr *client_addr;
        int connfd = accept(this->serverfd, client_addr, &client_len);
        std::cout << client_addr->sa_data << std::endl;
    }
    
}