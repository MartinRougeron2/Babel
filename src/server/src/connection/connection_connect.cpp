/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** connect.cpp
*/

#include <vector>
#include <string>

#include "handler.hpp"
#include "entry.hpp"
#include "server.hpp"
#include "logic.hpp"
#include "logs.hpp"

void connection_connect(std::vector<std::string> args, entry *ent)
{
    server *serv = NULL;
    std::vector<std::string> vec;

    if (args.size() == 0 || args[0].size() == 0) {
        ent->sendToClient(FailConnect, vec);
    } else {
        serv = (server *)ent->serv;
        if (serv->check_username(args[0])) {
            ent->pseudo = args[0];
            std::cout << COLOR_GREEN << LOGIN_SUCCESS << COLOR_RESET << ent->pseudo << std::endl;
            ent->sendToClient(SuccessConnect, vec);
        } else {
            ent->sendToClient(FailConnect, vec);
            std::cout << COLOR_RED << LOGIN_FAILED << COLOR_RESET << ent->pseudo << std::endl;
        }
    }
}