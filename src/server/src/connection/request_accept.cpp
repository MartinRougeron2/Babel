/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** request_accept.cpp
*/

#include <vector>
#include <string>

#include "handler.hpp"
#include "entry.hpp"
#include "server.hpp"
#include "logic.hpp"
#include "logs.hpp"

void connection_pending_accept(std::vector<std::string> args, entry *ent)
{
    std::vector<std::string> vec;
    server *serv;
    entry *contact;

    if (args.size() > 0) {
        serv = (server *)ent->serv;
        if (serv->check_username(args[0]) == true) {
            contact = serv->get_pseudo(args[0]);
            vec.push_back(contact->address);
            vec.push_back(std::to_string(contact->port));
            vec.push_back(contact->pseudo);
            ent->sendToClient(AddContact, vec);
            vec.clear();
            vec.push_back(ent->address);
            vec.push_back(std::to_string(ent->port));
            vec.push_back(ent->pseudo);
            contact->sendToClient(AddContact, vec);
            std::cout << ent->pseudo << REQUEST_ACCEPTED << args[0] << std::endl;
        }
    }
}
