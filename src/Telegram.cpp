//
// Created by User on 21.09.2022.
//

#include "../inc/Telegram.h"

void Telegram::send(const std::string &str) {

    for (const auto &i: _users_id) {
        _bot.getApi().sendMessage(i, str);
    }


    /*  bot.getEvents().onCommand("start", [&](TgBot::Message::Ptr message) {
          bot.getApi().sendMessage(message->chat->id, "Hi!");
      });
      bot.getEvents().onAnyMessage([&](TgBot::Message::Ptr message) {
          printf("User wrote %s\n", message->text.c_str());
          if (StringTools::startsWith(message->text, "/start")) {
              return;
          }
          bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
      });
      try {
          printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
          TgBot::TgLongPoll longPoll(bot);
          while (true) {
              printf("Long poll started\n");
              longPoll.start();
          }
      } catch (TgBot::TgException& e) {
          printf("error: %s\n", e.what());
      }*/
}

void Telegram::start() {
    _bot.getEvents().onAnyMessage([&](TgBot::Message::Ptr message) {
        //printf("User wrote %s\n", message->text.c_str());
/*        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }*/

        if (!check_user(message->from->id)) {
            _bot.getApi().sendMessage(message->chat->id, "У вас нет прав доступа к данному боту!!!");
        } else {
            _bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
            if (message->text == "/all") {
                _bot.getApi().sendMessage(message->chat->id, "command = all");
                is_get_all_hosts = true;
            }else{
                _bot.getApi().sendMessage(message->chat->id, "command = not all");
            }
        }
    });



    try {
        //printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(_bot);
        printf("Long poll started\n");
        while (true) {
            longPoll.start();
        }
    } catch (TgBot::TgException &e) {
        printf("error: %s\n", e.what());
    }

}

bool Telegram::check_user(std::int64_t id) {
    for (const auto &i: _users_id) {
        if (i == id) return true;
    }

    return false;
}


