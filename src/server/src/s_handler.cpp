/*
** EPITECH PROJECT, 2019
** handler.cpp
** File description:
** handler
*/

// # Lib Imports

#include <iostream>
#include <vector>

// # Local Imports

#include "c_handler.hpp"
#include "handler.hpp"
#include "entity.hpp"

// # Methods

static void (*servHandlers[17])(std::vector<std::string> args, entity *ent) = {
    HandleWelcome,
    HandleConnect,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    HandlePendingRequest,
    NULL,
    NULL,
    NULL,
    HandleAcceptPending,
    HandleRefusePending,
    NULL,
    NULL,
    NULL,
    NULL
};

void dispatchPacket(int id, std::vector<std::string> args, entity *ent)
{
    if (servHandlers[id] == NULL)
        return;
    servHandlers[id](args, (entity *)ent);
}

void handlePacket(std::string data, entity *ent)
{
    std::string token;
    std::vector<std::string> args;
    int size = 0;
    int id = -1;

    if (data.length() == 0)
        return;
    if (data.find(" ") != std::string::npos) {
        for (size_t pos = 0; (pos = data.find(" ")) != std::string::npos; size++) {
            std::string token = data.substr(0, pos);
            if (size == 0)
                id = manageId(token);
            else
                args.push_back(token);
            data.erase(0, pos + 1);
        }
        if (data.length())
            args.push_back(data);
    } else
        id = manageId(data);
    if (id >= 0 && id <= 17)
        dispatchPacket(id, args, ent);
}

int manageId(std::string data)
{
    if (data.length() == 0)
        return (-1);
    for (unsigned int i = 0; i < data.length(); i++)
        if (!(data[i] <= '9' && data[i] >= '0'))
            return (-1);
    int val = atoi(data.c_str());
    return (val);
}

