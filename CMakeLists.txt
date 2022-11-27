cmake_minimum_required(VERSION 3.18)
project(ping)

set(CMAKE_CXX_STANDARD 20)
set(Boost_USE_MULTITHREADED ON)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

add_executable(ping main.cpp inc/colormod.h inc/func.h src/Ping.cpp inc/Ping.h src/Parser.cpp inc/Parser.h inc/Telegram.h src/Telegram.cpp src/Host.cpp inc/Host.h)

target_link_libraries(ping /usr/local/lib/libTgBot.a ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})
