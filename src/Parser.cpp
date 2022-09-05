//
// Created by User on 03.09.2022.
//

#include "../inc/Parser.h"


std::vector<std::vector<std::string>> Parser::getList() {
    std::ifstream f("../ip.ini");
    std::vector<std::vector<std::string>> vector_result{};
    std::vector<std::string> vec{};
    std::string str{};
    while(f){
        vec.clear();
        std::getline(f, str);
        if (str.empty()) continue;
        auto iter = std::find(str.begin(), str.end(), ':');
        std::string a(str.begin(), iter);
        std::string b(iter+1, (str.end() - 1));
        vec.push_back(a);
        vec.push_back(b);
        vector_result.push_back(vec);
    }
    f.close();
    return vector_result;
}
