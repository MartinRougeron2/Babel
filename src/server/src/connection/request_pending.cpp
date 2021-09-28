/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** request_pending.cpp
*/

#include <vector>
#include <string>

#include "handler.hpp"
#include "entry.hpp"
#include "server.hpp"
#include "logic.hpp"
#include "logs.hpp"

void connection_pending(std::vector<std::string> args, entry *ent)
{
    std::vector<std::string> vec;
    if (args.size() == 0) {
        ent->sendToClient(PendingFail, vec);
        return;
    }
    server *serv = (server *)ent->serv;
    if (!serv->check_username(args[0])) {
        entry *contact = serv->get_pseudo(args[0]);
        vec.push_back(ent->pseudo);
        contact->sendToClient(PendingInfo, vec);
        vec.clear();
        ent->sendToClient(PendingSuccess, vec);
        std::cout << ent->pseudo << REQUEST_SENT << args[0] << std::endl;
    } else {
        ent->sendToClient(PendingFail, vec);
        std::cout << REQUEST_UNKNOWN << args[0] << std::endl;
    }
}