/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** main.cpp
*/

#include "../../include/server/Asio.hpp"

#include "../../include/server/Signals.hpp"
#include "../../include/server/TCP.hpp"
#include "../../include/server/UDP.hpp"

typedef std::deque<chat_message> chat_message_queue;
typedef std::shared_ptr<chat_participant> chat_participant_ptr;

int main(int ac, char **argv)
{
    boost::asio::io_service io_service;
    std::list<chat_server> servers;

    signals::handler();
    TCP tcp_server = TCP();
    try {
        for (int i = 1; i < ac; i++) {
            tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[i]));
            servers.emplace_back(io_service, endpoint);
        }
        io_service.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return (0);
}