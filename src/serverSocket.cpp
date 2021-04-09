#include "serverSocket.h"
#include "config.h"
#include <iostream>

ServerSocket::ServerSocket(config host)
{
    this->host=host;
    if((this->serverfd = socket(this->host.getDomain(),SOCK_STREAM,0))==-1){
        std::cout<<"socket create fail\n";
        exit(1);
    }else
        std::cout<<"socket create success\n";
}

ServerSocket::~ServerSocket()
{
}