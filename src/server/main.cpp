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
    __attribute__((unused)) TCPServer tcpServer(ios, TCP_PORT);
    __attribute__((unused)) tcp::endpoint endpoint(tcp::v4(), TCP_PORT);
    __attribute__((unused)) UdpServer udpServer(ios);

    try {
        signals::handler();
        boost::thread_group group;

        for (unsigned i = 0; i < std::thread::hardware_concurrency(); ++i)
            group.create_thread(bind(&boost::asio::io_service::run, boost::ref
                (ios)));
        ios.run();
        std::cout << "lol\n";

        group.join_all();
        // ios.run();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return (0);
}
