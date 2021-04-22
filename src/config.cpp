#include "config.h"

config::config(std::string path, std::string domain)
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
        if (key == "domain")
            continue;
        std::cout << key << ":" << value << '\n';
        configData.insert({key, value});
    }
    if (domain == "ipv4" || domain == "ipv6")
    {
        this->configData.insert({"domain",domain});
    }
    else
    {
        this->configData.insert({"domain","ipv4"});
        std::cout << "unrecognized domain. has been set to ipv4\n";
    }
    std::cout << "domain:" << this->configData["domain"] << '\n';
}

config::config(std::string path)
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
    if (configData.find("domain") == configData.end())
    {
        this->configData.insert({"domain", "ipv4"});
        std::cout << "domain:ipv4\n";
    }
}