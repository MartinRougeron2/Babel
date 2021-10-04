/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** main.cpp
*/

#include "server/TCP.hpp"
#include "server/UdpServer.hpp"

int main(int argc, char **argv)
{
    boost::asio::io_service io_service;
    std::list<chat_server> servers;
    tcp::endpoint endpoint(tcp::v4(), TCP_PORT);

    try {
        servers.emplace_back(io_service, endpoint);
        signals::handler();
        UdpServer udpServer(io_service);
        io_service.run();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return (0);
}
