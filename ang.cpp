#include <fstream>
#include <string>
#include <iostream>
#include "./scr/config.h"

static const std::string configFile="../conf/config.txt";

int main(){
    config host(configFile);
    if(!host.empty())
        std::cout<<host.getPort();
    return 0;
}