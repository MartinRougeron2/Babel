/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** main.cpp
*/

#include "../../include/server/Aasio.hpp"

int main(int argc, char **argv)
{
    boost::asio::io_service io_service;

    try
    {
        if (argc != 2) {
            std::cerr << "Usage: async_udp_echo_server <port>" << std::endl;
            return (1);
        }

        server s(io_service, atoi(argv[1]));

        io_service.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return (0);
}
