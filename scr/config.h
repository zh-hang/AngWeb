#ifndef __CONFIG_H__
#define __CONFIG_H__
#include <map>
#include <string>
#include <fstream>
#include <iostream>

#define MAXLINE 256

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
        while (infile.getline (data, MAXLINE))
        {
            int i = 0;
            std::string key, value;
            bool flag = true;
            while (data[i])
            {
                if (data[i] == '='){
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
            std::cout<<key<<":"<<value<<'\n';
            configData.insert(std::pair<std::string, std::string>(key, value));
        }
    }
    ~config() {}
    std::string getHost()
    {
        return configData.at("host");
    }
    std::string getPort()
    {
        return configData.at("port");
    }
    bool empty(){
        return configData.empty();
    }
};

#endif