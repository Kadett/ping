#include <utility>

#include "../inc/Ping.h"
#include "../inc/colormod.h"
#include <algorithm>
#include <arpa/inet.h>


Ping::Ping(std::vector<std::vector<std::string>> vec) : _vec_input(std::move(vec)) {}

std::vector<std::string> Ping::ping(std::vector<std::string> &v) {
    std::string s{"ping -c1 -s1 " + v.at(1) + " > /dev/null 2>&1"};
    //std::cout << s << std::endl;
    int res = std::system(s.c_str());
    //std::cout << " res = " << res << std::endl;
    int count{0};
    while (res != 0 && count > 3) {
        res = std::system(s.c_str());
        count++;
    }
    std::vector<std::string> vector{};

    vector.push_back(v.at(0));

    vector.push_back(v.at(1));
    vector.emplace_back(res == 0 ? "OK" : "NOT");
    return vector;
}

void Ping::run() {
    std::mutex mutex;
    std::vector<std::thread *> th;
    for (auto &i: _vec_input) {
        th.push_back(new std::thread([&]() {
            auto r = this->ping(i);
            mutex.lock();
            _vec_result.push_back(r);
            mutex.unlock();
        }));
    }

    for (auto i: th) {
        i->join();
    }
}

void Ping::print() {
    std::sort(std::begin(_vec_result), std::end(_vec_result), [](const std::vector<std::string>& a, const std::vector<std::string>& b){
        in_addr addr1{};
        in_addr addr2{};
        inet_aton(a[1].c_str(), &addr1);
        inet_aton(b[1].c_str(), &addr2);

        return addr1.s_addr < addr2.s_addr;
    });

    for (auto &i: _vec_result) {
        //if(i.at(2) == "OK") continue;
        std::cout << i.at(0) << " - " << i.at(1) << " - " << (i.at(2) == "OK" ? Color::GREEN : Color::RED)  << i.at(2) << Color::DEF <<  std::endl;
    }
    /*for (auto &i: _vec_result) {
        if(i.at(2) == "NOT") continue;
        std::cout << i.at(0) << " - " << i.at(1) << " - " << (i.at(2) == "OK" ? Color::GREEN : Color::RED)  << i.at(2) << Color::DEF <<  std::endl;
    }*/
}
