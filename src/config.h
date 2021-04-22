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
    std::string config_file_path;

    std::map<std::string, std::string> config_data;

public:
    config() {}
    config(std::string host,std::string port, std::string domain);
    config(std::string path);
    ~config() {}

    std::string getHost()
    {
        return this->config_data["host"];
    }

    int getPort()
    {
        return std::stoi(this->config_data["port"]);
    }

    void setDomain(std::string domain)
    {
        if (domain == "ipv4" || domain == "ipv6")
        {
            this->config_data["domain"] = domain;
        }
        else
        {
            this->config_data["domain"] = "ipv4";
            std::cout << "unrecognized domain. has been set to ipv4\n";
        }
    }

    void setDomain(int domain)
    {
        if (domain == AF_INET)
        {
            this->config_data["domain"] = "ipv4";
        }
        else if (domain == AF_INET6)
        {
            this->config_data["domain"] = "ipv6";
        }
        else
        {
            this->config_data["domain"] = "ipv4";
            std::cout << "unrecognized domain. has been set to ipv4\n";
        }
    }

    int getDomain()
    {
        if (this->config_data.at("domain") == "ipv4")
            return AF_INET;
        if (this->config_data.at("domain") == "ipv6")
            return AF_INET6;
        return 0;
    }
    bool empty()
    {
        return this->config_data.empty();
    }
};

#endif