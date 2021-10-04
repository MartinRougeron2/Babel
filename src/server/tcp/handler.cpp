/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Handler.cpp
*/

#include "server/TCP.hpp"

Handler::Handler()
{
    return;
}

Handler::~Handler()
{
    return;
}

std::string Handler::connect(int id)
{
    std::cout << "connecting " << id << std::endl;

    return ("");
}

std::string Handler::disconnect(int id)
{
    std::cout << "disconnecting " << id << std::endl;

    return ("");
}

std::string Handler::join(int id)
{
    std::cout << "joinning " << id << std::endl;

    return ("");
}

std::string Handler::leave(int id)
{
    return ("");
}

std::string Handler::call(int id)
{
    return ("");
}

std::string Handler::ping(int id)
{
    std::cout << "pong" << std::endl;

    return ("");
}
