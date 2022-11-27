#include <iostream>
#include <chrono>
#include "inc/Parser.h"
#include "inc/Ping.h"
#include "inc/Telegram.h"
#include "inc/Host.h"
#include <tgbot/tgbot.h>
#include "inc/func.h"



using namespace std;


int main() {

    Ping p(Parser::getHosts());
    int count{0};
    while (true) {
        try {
            p.run();
            system("clear");
            p.print();
            ++count;
            std::cout << count << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
        catch (const std::exception& ex) {
            std::cerr << "ERROR3 - " << ex.what();
        }
    }

}




/*    Ping p(Parser::getHosts());
    int count{0};
    while (true) {
        p.run();
        system("clear");
        p.print();
        ++count;
        std::cout << count << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

}*/


//string s = MyFunc::exec("ping 10.0.100.7 -c3");

//std::cout << s;