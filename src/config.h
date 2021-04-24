#ifndef __CONFIG_H__
#define __CONFIG_H__
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sys/socket.h>

#define MAXLINE 1024

class config
{
    std::string configFilePath;

    std::map<std::string, std::string> configData;

public:
    config() {}
    config(std::string path, std::string domain);
    config(std::string path);
    ~config() {}

    std::string getHost()
    {
        return this->configData["host"];
    }

    int getPort()
    {
        return std::stoi(this->configData["port"]);
    }

    void setDomain(std::string domain)
    {
        if (domain == "ipv4" || domain == "ipv6")
        {
            this->configData["domain"] = domain;
        }
        else
        {
            this->configData["domain"] = "ipv4";
            std::cout << "unrecognized domain. has been set to ipv4\n";
        }
    }

    void setDomain(int domain)
    {
        if (domain == AF_INET)
        {
            this->configData["domain"] = "ipv4";
        }
        else if (domain == AF_INET6)
        {
            this->configData["domain"] = "ipv6";
        }
        else
        {
            this->configData["domain"] = "ipv4";
            std::cout << "unrecognized domain. has been set to ipv4\n";
        }
    }

    int getDomain()
    {
        if (this->configData.at("domain") == "ipv4")
            return AF_INET;
        if (this->configData.at("domain") == "ipv6")
            return AF_INET6;
        return 0;
    }
    bool empty()
    {
        return this->configData.empty();
    }
};

#endif