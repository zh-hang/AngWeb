#ifndef ServerSocket_class
#define ServerSocket_class

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "config.h"

#define MAX_LISTEN_NUM 256

class ServerSocket
{
private:
    int serverfd;
    config host;
    addrinfo *hostInfo;

public:
    ServerSocket(config host);
    ~ServerSocket();
    void run();
};

#endif