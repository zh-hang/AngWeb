#ifndef ServerSocket_class
#define ServerSocket_class

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include "config.h"

#define MAX_LISTEN_NUM 256

class ServerSocket
{
private:
    int serverfd;
    sockaddr_in host_addr;

public:
    ServerSocket(char const* host_str, char const *port);
    ~ServerSocket();
    void run();
};

class ServerSocket6
{
private:
    int serverfd;
    sockaddr_in6 host_addr;

public:
    ServerSocket6(char const* host_str, char const *port);
    ~ServerSocket6();
    void run();
};

#endif