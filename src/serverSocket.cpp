#include "serverSocket.h"
#include "config.h"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>

ServerSocket::ServerSocket(char const *host_str, char const *port) {
    addrinfo hint{}, *res;
    bzero(&hint, sizeof(addrinfo));
    hint.ai_flags = AI_PASSIVE;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_family = AF_INET;
//    if (getaddrinfo(host_str, port, &hint, &res) != 0) {
    if (getaddrinfo(NULL, port, &hint, &res) != 0) {
        std::cerr << "get address information fail\n";
        exit(errno);
    }
    if (res->ai_family != AF_INET) {
        std::cerr << "get address information fail\n";
        exit(errno);
    }
    std::cout << "get address information successfully\n";
    this->host_addr = *(sockaddr_in *) res->ai_addr;
    freeaddrinfo(res);

    this->serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->serverfd == -1) {
        std::cerr << "socket create fail\n";
        exit(errno);
    }
    std::cout << "socket create success\n" << "socket id:" << this->serverfd << std::endl;
}

ServerSocket::~ServerSocket() = default;

[[noreturn]] void ServerSocket::run() {
    if (bind(this->serverfd, (struct sockaddr *) &this->host_addr, sizeof(struct sockaddr)) != 0) {
        std::cout << "socket bind fail\n";
        exit(errno);
    }
    if (listen(this->serverfd, MAX_LISTEN_NUM) < 0) {
        std::cout << "listen fail\n";
        exit(errno);
    }
    std::cout << "listening...\n";
    while (1) {
        int client_fd;
        sockaddr_in client_addr{};
        socklen_t len = sizeof(sockaddr);
        client_fd = accept(this->serverfd, (sockaddr *) &client_addr, &len);
        if (client_fd == -1) {
            std::cerr << "cannot accept msg\n" << inet_ntoa(client_addr.sin_addr) << std::endl;
        } else {
            char buf[MAX_BUF];
            std::cout << "accept from " << inet_ntoa(client_addr.sin_addr) << std::endl;
            bzero(buf, MAX_BUF + 1);
            len = recv(client_fd, buf, MAX_BUF, 0);
            if (len > 0) {
                std::cout << "accept successfully:" << buf << "\n" << len << "byte data\n";
            } else {
                std::cout << "accept fail\n";
            }
        }
    }
}

ServerSocket6::ServerSocket6(char const *host_str, char const *port) {
    addrinfo hint{}, *res;
    bzero(&hint, sizeof(addrinfo));
    hint.ai_flags = AI_PASSIVE;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_family = AF_INET6;
//    if (getaddrinfo(host_str, port, &hint, &res) != 0) {
    if (getaddrinfo(NULL, port, &hint, &res) != 0) {
        std::cerr << "get address information fail\n";
        exit(errno);
    }
    if (res->ai_family != AF_INET6) {
        std::cerr << "get address information fail\n";
        exit(errno);
    }
    std::cout << "get address information successfully\n";
    this->host_addr = *(sockaddr_in6 *) res->ai_addr;
    freeaddrinfo(res);


    this->serverfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (this->serverfd == -1) {
        std::cerr << "socket create fail\n";
        exit(errno);
    }
    std::cout << "socket create success\n" << "socket id:" << this->serverfd << std::endl;
//    bzero(&this->host_addr, sizeof(sockaddr_in6));
//    if (inet_pton(AF_INET6, host_str, &(this->host_addr)) < 0) {
//        std::cout << "address create fail\n";
//        exit(-1);
//    }
//    this->host_addr.sin6_family = AF_INET6;
//    this->host_addr.sin6_port = htons(port);
//    this->host_addr.sin6_addr = in6addr_any;
//    std::cout << "address create successfully\n";
}

ServerSocket6::~ServerSocket6() = default;

[[noreturn]] void ServerSocket6::run() {
    if (bind(this->serverfd, (sockaddr *) &this->host_addr, sizeof(sockaddr_in6)) == -1) {
        std::cerr << "socket bind fail\n";
        exit(errno);
    }
    std::cout << "bind successfully\n";
    if (listen(this->serverfd, MAX_LISTEN_NUM) < 0) {
        std::cerr << "listen fail\n";
        exit(errno);
    }
    std::cout << "listen...\n";
    while (1) {
        int client_fd;
        char buf[MAX_BUF];
        sockaddr_in6 client_addr{};
        socklen_t len = sizeof(sockaddr);
        client_fd = accept(this->serverfd, (sockaddr *) &client_addr, &len);
        if (client_fd == -1) { ;
            std::cerr << "cannot accept msg\n" <<
                      inet_ntop(AF_INET6, &client_addr.sin6_addr, buf, sizeof(buf)) << std::endl;
        } else {
            std::cout << "accept from " <<
                      inet_ntop(AF_INET6, &client_addr.sin6_addr, buf, sizeof(buf)) << std::endl;
            bzero(buf, MAX_BUF + 1);
            len = recv(client_fd, buf, MAX_BUF, 0);
            if (len > 0) {
                std::cout << "accept successfully:" << buf << "\n" << len << "byte data\n";
            } else {
                std::cout << "accept fail\n";
            }
        }
    }
}