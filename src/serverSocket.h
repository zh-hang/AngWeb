#ifndef ServerSocket_class
#define ServerSocket_class

#include <sys/socket.h>
#include <sys/types.h>
#include "config.h"

class ServerSocket
{
private:
    int serverfd;
    config host;

public:
    ServerSocket(config host);
    ~ServerSocket();
    void run();
};

#endif