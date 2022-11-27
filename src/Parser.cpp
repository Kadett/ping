//
// Created by User on 03.09.2022.
//

#include "../inc/Parser.h"


std::vector<Host> Parser::getHosts() {
    std::ifstream f("../ip.ini");
    std::vector<Host> vector_hosts{};
    std::string str{};
    while(f){
        std::getline(f, str);
        if (str.empty()) continue;
        if (str[0] == '#') continue;
        auto iter = std::find(str.begin(), str.end(), ':');
        std::string a(str.begin(), iter);
        std::string b(iter+1, (str.end() - 1));
        vector_hosts.push_back(*new Host(a, b));
    }
    f.close();
    return vector_hosts;
}
