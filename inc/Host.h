#pragma once
#include <iostream>
#include <sstream>




class Host {

public:
    Host(std::string desc, std::string ip) : desc(std::move(desc)), ip(std::move(ip)), isAvailable(false){}

    std::string ip;
    std::string desc;
    bool isAvailable;

    friend bool operator > (const Host &h1, const Host &h2);
    friend bool operator < (const Host &h1, const Host &h2);
    friend bool operator == (const Host &h1, const Host &h2);
    friend bool operator != (const Host &h1, const Host &h2);


};


