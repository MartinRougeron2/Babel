/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** main.cpp
*/

#include "../../include/server/Asio.hpp"

#include "../../include/server/Signals.hpp"

typedef std::deque<chat_message> chat_message_queue;
typedef std::shared_ptr<chat_participant> chat_participant_ptr;

int main(int argc, char* argv[])
{
    boost::asio::io_service io_service;
    std::list<chat_server> servers;

    try
    {
        signals::handler();
        if (argc < 2) {
            std::cerr << "Usage: babel_server <port> [<port> ...]" << std::endl;
            return (1);
        }
        for (int i = 1; i < argc; i++) {
            tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[i]));
            servers.emplace_back(io_service, endpoint);
        }

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

  return 0;
}