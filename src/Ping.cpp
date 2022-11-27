#include <utility>

#include "../inc/Ping.h"
#include "../inc/colormod.h"
#include <algorithm>



//Ping::Ping(std::vector<Host> vector_hosts, Telegram& telegram) : _vec_all_hosts(std::move(vector_hosts)) {}

Ping::Ping(std::vector<Host> vector_hosts) : _vec_all_hosts(std::move(vector_hosts)), _first_run{true} {

    sort(_vec_all_hosts);
    _vec_last_state_hosts = _vec_all_hosts;
    std::thread th([&]() {
        tel.start();

    });
    std::thread th1([&]() {
        check_telegram();
    });
    th.detach();
    th1.detach();
}

Host Ping::ping(const Host &host) {
    Host h(host.desc, host.ip);
    std::string s{"ping -c1 -s1 " + host.ip + " > /dev/null 2>&1"};
    try {
        int res = std::system(s.c_str());
        int count{0};
        while (res != 0 && count < 3) {
            count++;
            res = std::system(s.c_str());
        }
        if (res == 0) h.isAvailable = true;
        else h.isAvailable = false;
    }
    catch (std::exception& ex){
        std::cerr << "ERROR1 - " << ex.what();
    }
    return h;
}

void Ping::run() {
    //std::mutex mutex;
    std::vector<std::thread *> th;
    _vec_hosts_result.clear();
    for (auto &i: _vec_all_hosts) {
        th.push_back(new std::thread([&]() {
            try {

                auto r = this->ping(i);

                _mut.lock();
                _vec_hosts_result.push_back(r);
                _mut.unlock();
            }
            catch (const std::exception& er){
                std::cerr << "ERROR2 - " << er.what();
                std::this_thread::sleep_for(std::chrono::seconds(5));
            }
        }));
    }

    for (auto i: th) {
        i->join();
    }
    sort(_vec_hosts_result);
    //-------------------------------------//

    if (_first_run){
        _vec_last_state_hosts = _vec_hosts_result;
        _last_date_time = exec("date");
        sendMessage(create_message_all_hosts(_vec_hosts_result));
        _first_run = false;
    }
    if(check_changes()){
        sendMessage(create_message_changes_hosts());
    }

    for (auto &i: th) delete i;
    _vec_last_state_hosts = _vec_hosts_result;
    _last_date_time = exec("date");

}

void Ping::print() {

    for (const auto &i: _vec_hosts_result) {
        if (i.isAvailable) continue;
        std::cout << i.desc << " - " << i.ip << " - " << Color::RED << "NOT"
                  << Color::DEF << std::endl;

    }
    for (const auto &i: _vec_hosts_result) {
        if (!i.isAvailable) continue;
        std::cout << i.desc << " - " << i.ip << " - " << Color::GREEN << "OK"
                  << Color::DEF << std::endl;

    }
}


void Ping::sort(std::vector<Host> &vec) {

    std::sort(vec.begin(), vec.end(), std::greater<>());

}

void Ping::sendMessage(const std::string &str) {
    tel.send(str);
}

std::string Ping::create_message_all_hosts(const std::vector<Host> &h) {
    std::stringstream ss;
    _mut.lock();
    for (const auto &i: h) {
        ss << (i.isAvailable ? "✅" : "❌") << " - " << i.ip << " - " << i.desc << "\n";
    }
    _mut.unlock();
    ss << '\n' << "last update:\n" << _last_date_time;

    return ss.str();
}

void Ping::check_telegram() {
    while (true) {
        if (tel.is_get_all_hosts) {
            sendMessage("command /all OK");
            sendMessage(create_message_all_hosts(_vec_last_state_hosts));
            tel.is_get_all_hosts = false;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

bool Ping::check_changes() {
    if (_vec_hosts_result != _vec_last_state_hosts) return true;
    return false;
}

std::string Ping::create_message_changes_hosts() {
    std::stringstream ss;
    _mut.lock();
    if (_vec_last_state_hosts.size() != _vec_hosts_result.size()){
        throw "ERROR 1";
        exit(333);
    }
    for (int i = 0; i < _vec_hosts_result.size(); ++i) {
        if (_vec_hosts_result.at(i) == _vec_last_state_hosts.at(i)) continue;
        else {
            ss << "state change:\n";
            ss << (_vec_hosts_result.at(i).isAvailable ? "✅" : "❌") << " - " << _vec_hosts_result.at(i).ip << " - " << _vec_hosts_result.at(i).desc << "\n";
        }
    }
    _mut.unlock();
    return ss.str();
}

std::string Ping::exec(const std::string& command) {
    char buffer[512];
    std::string result;

    // Open pipe to file
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "popen failed!";
    }

    // read till end of process:
    while (!feof(pipe)) {

        // use buffer to read and add to result
        if (fgets(buffer, 512, pipe) != NULL)
            result += buffer;
    }

    pclose(pipe);
    return result;
}



















