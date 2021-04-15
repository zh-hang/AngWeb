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
    sockaddr_in hostAddr;

public:
    ServerSocket(config host);
    ~ServerSocket();
    void run();
};

#endif