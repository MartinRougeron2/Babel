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

void HandleConnect(std::vector<std::string> args, entry *ent)
{
    std::vector<std::string> vec;

    if (args.size() == 0 || args[0].size() == 0) {
        ent->sendToClient(FailConnect, vec);
    } else {
        server *serv = (server *)ent->serv;
        if (serv->isPseudoAvailable(args[0])) {
            ent->pseudo = args[0];
            std::cout << COLOR_GREEN << LOGIN_SUCCESS << COLOR_RESET << ent->pseudo << std::endl;
            ent->sendToClient(SuccessConnect, vec);
        } else {
            ent->sendToClient(FailConnect, vec);
            std::cout << COLOR_RED << LOGIN_FAILED << COLOR_RESET << ent->pseudo << std::endl;
        }
    }
}