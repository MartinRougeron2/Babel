/*
** EPITECH PROJECT, 2019
** connectionHander.cpp
** File description:
** connectionHandler
*/

// # Lib Imports

#include <vector>
#include <string>

// # Local Imports

#include "handler.hpp"
#include "entity.hpp"
#include "server.hpp"
#include "logic.hpp"

// # Methods

// 000 {port} | New client say hello and give his port number for the Call Server
void HandleWelcome(std::vector<std::string> args, entity *ent)
{
    if (args.size() < 1 || atoi(args[0].c_str()) <= 0)
        return;
    ent->port = atoi(args[0].c_str());
    std::cout << "Port define for unknow user : " << std::to_string(ent->port) << std::endl;
}

// 001 {pseudo} | New client want to login with username
void HandleConnect(std::vector<std::string> args, entity *ent)
{       
    std::vector<std::string> vec;
    if (args.size() == 0 || args[0].size() == 0) {
        ent->sendToClient(FailConnect, vec);
        return;
    }
    server *serv = (server *)ent->serv;
    if (serv->isPseudoAvailable(args[0])) {
        ent->pseudo = args[0];
        std::cout << "User login with pseudonyme : " << ent->pseudo << std::endl;
        ent->sendToClient(SuccessConnect, vec);
    } else {
        ent->sendToClient(FailConnect, vec);
        std::cout << "User login failed with pseudonyme : " << ent->pseudo << std::endl;
    }
}

// 007 {pseudo} | Client want to send a friend invite
void HandlePendingRequest(std::vector<std::string> args, entity *ent)
{
    std::vector<std::string> vec;
    if (args.size() == 0) {
        ent->sendToClient(PendingFail, vec);
        return;
    }
    server *serv = (server *)ent->serv;
    if (!serv->isPseudoAvailable(args[0])) {
        entity *contact = serv->getClientByPseudo(args[0]);
        vec.push_back(ent->pseudo);
        contact->sendToClient(PendingInfo, vec);
        vec.clear();
        ent->sendToClient(PendingSuccess, vec);
        std::cout << ent->pseudo << " sent friend invitation to " << args[0] << std::endl;
    } else {
        ent->sendToClient(PendingFail, vec);
        std::cout << "Can't found any user with this name : " << args[0] << std::endl;
    }
}
// 011 {pseudo} | Client accepted friend invite
void HandleAcceptPending(std::vector<std::string> args, entity *ent)
{
    std::vector<std::string> vec;
    server *serv;
    entity *contact;

    if (args.size() == 0)
        return;
    serv = (server *)ent->serv;
    if (serv->isPseudoAvailable(args[0]))
        return;
    contact = serv->getClientByPseudo(args[0]);
    vec.push_back(contact->address);
    vec.push_back(std::to_string(contact->port));
    vec.push_back(contact->pseudo);
    ent->sendToClient(AddContact, vec);
    vec.clear();
    vec.push_back(ent->address);
    vec.push_back(std::to_string(ent->port));
    vec.push_back(ent->pseudo);
    contact->sendToClient(AddContact, vec);
    std::cout << ent->pseudo << " accepted friend invitation from " << args[0] << std::endl;
}
// 012 {pseudo} | Client refused friend invite
void HandleRefusePending(std::vector<std::string> args, entity *ent)
{
    server *serv;
    //entity *contact;

    if (args.size() == 0)
        return;
    serv = (server *)ent->serv;
    if (serv->isPseudoAvailable(args[0]))
        return;
    //contact = serv->getClientByPseudo(args[0]);
    std::cout << ent->pseudo << " refused friend invitation from " << args[0] << std::endl;
}
