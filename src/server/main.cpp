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
    boost::asio::io_service ios;
    Server s(ios, TCP_PORT);

    try {
        signals::handler();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return (0);
}
