#pragma once

#include <iostream>
#include <tuple>
#include <vector>
#include <thread>
#include <mutex>
#include "Telegram.h"
#include "Host.h"



class Ping {

public:
    //Ping(std::vector<Host> vector_hosts, Telegram &telegram);
    Ping(std::vector<Host> vector_hosts);
    //Ping(std::string str);


    void run();

    void print();


private:
    Telegram tel{};
    std::vector<Host> _vec_all_hosts{};
    std::vector<Host> _vec_hosts_result{};
    std::vector<Host> _vec_last_state_hosts{};
    std::mutex _mut;
    bool _first_run;
    std::string _last_date_time{};
    std::string exec(const std::string& command);

private:

    Host ping(const Host &host);

    //bool compare_IP(const std::string &ip1, const std::string &ip2);

    std::string create_message_changes_hosts();

    std::string create_message_all_hosts(const std::vector<Host> &h);

    bool check_changes();

    void sendMessage(const std::string &str);

    void sort(std::vector<Host> &vec);

    void check_telegram();
};
