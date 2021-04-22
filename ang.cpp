#include <fstream>
#include <string>
#include <iostream>
#include "./src/config.h"
#include "./src/serverSocket.h"

static const std::string configFile = "../conf/config.txt";

int main(int argc, char *argv[])
{
    config host;

    switch (argc)
    {
    case 1:
        host = config(configFile);
        break;
    case 2:
    {
        try
        {
            host = config(configFile, std::string(argv[1]));
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            return 0;
        }
    }
    break;
    default:
        std::cout << "unrecognized parameters:";
        for (int i = 2; i < argc; i++)
        {
            std::cout << "" << argv[i];
        }
        return 0;
    }

    if (host.getDomain() == AF_INET)
    {
        ServerSocket server(host.getHost().c_str(), host.getPort());
        server.run();
    }
    else if (host.getDomain() == AF_INET6)
    {
        ServerSocket6 server(host.getHost().c_str(), host.getPort());
        server.run();
    }

    return 0;
}