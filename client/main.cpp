#include <cstdio>
#include <cstring>
#include <cerrno>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <netdb.h>

#define MAX_BUF 1024

int main(int argc, char **argv) {
    int sockfd, len, stat;
    char buffer[MAX_BUF + 1];
    addrinfo hints{};
    addrinfo *result, *rp;
    sockaddr_in dest{}; // IPv4
    sockaddr_in6 dest6{};      // IPv6
    const char *msg = "this is client\n";

    if (argc != 4) {
        std::cout << "参数格式错误！正确用法如下：/n/t/t" << argv[0] << " IP地址 端口 IP Version/n/t比如:/t" << argv[0]
                  << " 127.0.0.1 80 ipv4/n此程序用来从某个 IP 地址的服务器某个端口接收最多 1024 个字节的消息";
        exit(0);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_ADDRCONFIG;


    /* 创建一个 socket 用于 tcp 通信 */
    if (strcmp(argv[3],"ipv6") == 0) {
        std::cout<<"by ipv6\n";
        hints.ai_family = AF_INET6;
        stat = getaddrinfo(argv[1], argv[2], &hints, &result);
        if (stat != 0) {
            std::cerr << "get address information fail\n";
            exit(EXIT_FAILURE);
        }
        dest6 = *(sockaddr_in6 *) result->ai_addr;
        std::cout << "get address information successfully\n";
        freeaddrinfo(result);

        sockfd = socket(AF_INET6, SOCK_STREAM, 0);
        if (sockfd < 0) {
            std::cerr << "create socket fail\n";
            exit(errno);
        }
        std::cout << "socket created successfully\n";

        stat = connect(sockfd, (sockaddr *) &dest6, sizeof(dest6));
        if (stat != 0) {
            std::cerr << "connect fail\n";
            exit(errno);
        }
        std::cout << "connect successfully\n";

        stat = send(sockfd, msg, strlen(msg), 0);
        if (stat < 0) {
            std::cerr << "send message fail\n";
            exit(errno);
        }
        std::cout << "send successfully";
        close(sockfd);
    }else{
        std::cout<<"by ipv4\n";
        hints.ai_family = AF_INET;
        stat = getaddrinfo(argv[1], argv[2], &hints, &result);
        if (stat != 0) {
            std::cerr << "get address information fail\n";
            exit(EXIT_FAILURE);
        }
        dest = *(sockaddr_in *) result->ai_addr;
        std::cout << "get address information successfully\n";
        freeaddrinfo(result);

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            std::cerr << "create socket fail\n";
            exit(errno);
        }
        std::cout << "socket created successfully\n";

        stat = connect(sockfd, (sockaddr *) &dest, sizeof(dest));
        if (stat != 0) {
            std::cerr << "connect fail\n";
            exit(errno);
        }
        std::cout << "connect successfully\n";

        stat = send(sockfd, msg, strlen(msg), 0);
        if (stat < 0) {
            std::cerr << "send message fail\n";
            exit(errno);
        }
        std::cout << "send successfully";
        close(sockfd);
    }

    return 0;
}