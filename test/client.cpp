#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <typeinfo>

#define MAXBUF 1024

int main(int argc, char **argv)
{
    int sockfd, len;
    struct sockaddr_in dest;
    char buffer[MAXBUF];

    if (argc != 3)
    {
        std::cout << "参数格式错误！正确用法如下：\n\t\t" << argv[0] << " IP地址 端口\n\t" << argv[0] << "127.0.0.1 80\n此程序用来从某个IP地址的服务器某个端口接受最多MAXBUF个字节\n";
        exit(0);
    }
    if((sockfd=socket(AF_INET,SOCK_STREAM,0)<0)){
        std::cout<<"创建socket失败\n";
        exit(0);
    }
    std::cout<<"socket created successful\n";
    dest.sin_family=AF_INET;
    dest.sin_port=htons(atoi(argv[2]);
    dest.sin_addr.s_addr = inet_addr(argv[1]);
    bzero(&(dest.sin_zero),8);
    std::cout<<"server address created successful\n"<<dest.sin_port<<" "<<dest.sin_addr.s_addr<<std::endl;
    if (connect(sockfd, (struct sockaddr *) &dest, sizeof(struct sockaddr)) != 0) {
        std::cout<<"connect server fail\n";
        exit(0);
    }
    std::cout<<"connect server successfully\n";
    close(sockfd);
    return 0;
}