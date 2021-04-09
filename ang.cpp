#include <fstream>
#include <string>
#include <iostream>
#include "./src/config.h"

static const std::string configFile="../conf/config.txt";

int main(){
    config host(configFile);
    return 0;
}