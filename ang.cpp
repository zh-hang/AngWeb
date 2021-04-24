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
    case 4:
    {
        try
        {
            host = config(std::string(argv[1]),std::string(argv[2]) ,std::string(argv[3]));
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
        for (int i = 1; i < argc; i++)
        {
            std::cout << "" << argv[i];
        }
        std::cout<<"\nplease input as ./server host port domain\n";
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