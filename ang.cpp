#include <fstream>
#include <string>
#include <iostream>
#include "./src/config.h"
#include "./src/serverSocket.h"

static const std::string configFile="../conf/config.txt";

int main(){
    config host(configFile);
    ServerSocket server(host.getHost(),host.getPort(),host.getDomain());
    server.run();
    return 0;
}