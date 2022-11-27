#pragma once
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
namespace MyFunc {
/*    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }*/



    string exec(string command) {
        char buffer[128];
        string result = "";

        // Open pipe to file
        FILE* pipe = popen(command.c_str(), "r");
        if (!pipe) {
            return "popen failed!";
        }

        // read till end of process:
        while (!feof(pipe)) {

            // use buffer to read and add to result
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }

        pclose(pipe);
        return result;
    }

}

