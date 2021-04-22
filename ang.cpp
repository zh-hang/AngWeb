#include <fstream>
#include <string>
#include <iostream>
#include "./src/config.h"
#include "./src/serverSocket.h"

static const std::string configFile="../conf/config.txt";

int main(argv[]){
    config host(configFile);
    
    ServerSocket server(host.getHost().c_str(),host.getPort(),host.getDomain());
    server.run();
    return 0;
}