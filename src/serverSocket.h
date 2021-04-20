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
    sockaddr_in hostAddr;

public:
    ServerSocket(const std::string host,const unsigned int port,const int domain_type);
    ~ServerSocket();
    void run();
};

#endif