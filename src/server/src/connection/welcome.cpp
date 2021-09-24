/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** welcome.cpp
*/

#include <vector>
#include <string>

#include "handler.hpp"
#include "entry.hpp"
#include "server.hpp"
#include "logic.hpp"
#include "logs.hpp"

void HandleWelcome(std::vector<std::string> args, entry *ent)
{
    if (args.size() < 1 || atoi(args[0].c_str()) <= 0)
        return;
    ent->port = atoi(args[0].c_str());
    std::cout << PORT_DEFINED << std::to_string(ent->port) << std::endl;
}