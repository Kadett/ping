#include <iostream>
#include "inc/Parser.h"
#include "inc/Ping.h"
#include <arpa/inet.h>





int main() {
    in_addr a{};
    inet_aton("10.10.10.10", &a);
    a.s_addr;
    std::vector<std::vector<std::string>> vec1;
    for (int i = 1; i < 255; ++i) {
        std::vector<std::string> v;
        v.emplace_back("test");
        v.push_back("10.10.10." + std::to_string(i));
        vec1.push_back(std::move(v));
    }
    //Ping p(Parser::getList());
    Ping p(vec1);

    p.run();
    p.print();

}