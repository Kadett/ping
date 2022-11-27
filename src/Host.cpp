//
// Created by User on 23.09.2022.
//

#include "../inc/Host.h"

bool operator>(const Host &h1, const Host &h2) {
    std::istringstream s1{h1.ip};
    std::istringstream s2{h2.ip};
    std::string str1, str2;
    while (std::getline(s1, str1, '.')) {
        std::getline(s2, str2, '.');
        int l = std::stoi(str1);
        int r = std::stoi(str2);
        if (l == r) continue;
        else if (l < r) return true;
        return false;
    }
    return false;
}

bool operator<(const Host &h1, const Host &h2) {
    return !(h1 > h2);
}

bool operator==(const Host &h1, const Host &h2) {
    return h1.isAvailable == h2.isAvailable && h1.ip == h2.ip;
}

bool operator!=(const Host &h1, const Host &h2) {
    return !(h1 == h2);
}