#pragma once

#include <cstdio>
#include <iostream>
#include <vector>
#include <tgbot/tgbot.h>

class Telegram {

public:
    Telegram() : _bot("5523211653:AAG2KNCVokoNBseupJLuKDARru5wz6hl-hs") {
        _users_id.emplace_back(523320321);
    }

    void send(const std::string &str);
    void start();

    bool is_get_all_hosts{false};
    bool is_get_host{false};

private:
    TgBot::Bot _bot;
    std::vector<std::int64_t> _users_id;
private:
    bool check_user(std::int64_t id);
};

