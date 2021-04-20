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
    config(std::string path)
    {
        configFilePath = path;
        std::ifstream infile;
        infile.open(configFilePath);
        char data[MAXLINE];
        while (infile.getline(data, MAXLINE))
        {
            int i = 0;
            std::string key, value;
            bool flag = true;
            while (data[i])
            {
                if (data[i] == '=')
                {
                    flag = false;
                    i++;
                    continue;
                }
                if (flag)
                    key.push_back(data[i]);
                else
                    value.push_back(data[i]);
                i++;
            }
            std::cout << key << ":" << value << '\n';
            configData.insert({key, value});
        }
    }
    ~config() {}

    std::string getHost(){
        return this->configData["host"];
    }

    int getPort(){
        return std::stoi(this->configData["port"]);
    }

    int getDomain()
    {
        if (configData.find("domain") == configData.end() || configData.at("domain") == "ipv4")
            return AF_INET;
        if (configData.at("domain") == "ipv6")
            return AF_INET6;
        return 0;
    }
    bool empty()
    {
        return configData.empty();
    }
};

#endif