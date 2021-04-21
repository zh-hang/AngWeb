#include "config.h"

config::config(std::string path, std::string domain)
{
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
        configData.insert({"domain", domain});
    }
}

config::config(std::string path)
{

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
        if(configData.find("domain")==configData.end()){
            this->configData.insert({"domain","ipv4"});
        }
    }
}