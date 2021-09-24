/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** request_refuse.cpp
*/

#include <vector>
#include <string>

#include "handler.hpp"
#include "entry.hpp"
#include "server.hpp"
#include "logic.hpp"
#include "logs.hpp"

void HandleRefusePending(std::vector<std::string> args, entry *ent)
{
    server *serv;

    if (args.size() == 0)
        return;
    serv = (server *)ent->serv;
    if (serv->isPseudoAvailable(args[0]))
        return;

    std::cout << ent->pseudo << REQUEST_REFUSED << args[0] << std::endl;
}
