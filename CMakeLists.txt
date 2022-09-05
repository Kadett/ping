cmake_minimum_required(VERSION 3.18)
project(ping)

set(CMAKE_CXX_STANDARD 20)


add_executable(ping main.cpp inc/colormod.h inc/func.h src/Ping.cpp inc/Ping.h src/Parser.cpp inc/Parser.h)
