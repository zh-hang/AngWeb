#include "config.h"

config::config(std::string host,std::string port, std::string domain)
{
    this->config_file_path="";
    this->config_data.insert({"host",host});
    this->config_data.insert({"port",port});
    if (domain == "ipv4" || domain == "ipv6")
    {
        this->config_data.insert({"domain",domain});
    }
    else
    {
        this->config_data.insert({"domain","ipv4"});
        std::cout << "unrecognized domain. has been set to ipv4\n";
    }
    for (auto i:this->config_data)
    {
        std::cout<<i.first<<":"<<i.second<<std::endl;
    }
    
}

config::config(std::string path)
{

    config_file_path = path;
    std::ifstream infile;
    infile.open(config_file_path);
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
        config_data.insert({key, value});
    }
    if (config_data.find("domain") == config_data.end())
    {
        this->config_data.insert({"domain", "ipv4"});
        std::cout << "domain:ipv4\n";
    }
}