#pragma once
#include <iostream>
#include <tuple>
#include <vector>
#include <thread>
#include <mutex>




class Ping {
public:
    Ping(std::vector<std::vector<std::string>> vec);

    void run();

    void print();

private:
    std::vector<std::vector<std::string>> _vec_input;
    std::vector<std::vector<std::string>> _vec_result;


public:

    std::vector<std::string> ping(std::vector<std::string>& v);
};
