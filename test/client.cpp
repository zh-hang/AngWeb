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
    std::string address=argv[1];
    int port=argv[2];
    Socket socket(address, port, wings::SOCKET_TYPE::IPV4);
    for (int i = 0; i < 10; ++i) {
        socket.write("This is Client4 Message.");
        char *reply = new char[1024];
        socket.read(reply, 1024);
        std::cout << reply << std::endl;
        delete[] reply;
    }
    socket.close();

    return 0;
}