/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** s_handler.cpp
*/

#include <iostream>
#include <vector>

#include "connection.hpp"
#include "handler.hpp"
#include "entry.hpp"

static void (*servHandlers[17])(std::vector<std::string> args, entry *ent) = {
    connection_welcome,
    connection_connect,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    connection_pending,
    NULL,
    NULL,
    NULL,
    connection_pending_accept,
    connection_pending_refuse,
    NULL,
    NULL,
    NULL,
    NULL
};

void dispatchPacket(int id, std::vector<std::string> args, entry *ent)
{
    if (servHandlers[id] != NULL)
        servHandlers[id](args, (entry *)ent);
}

void packet_handler(std::string data, entry *ent)
{
    int size = 0;
    int id = -1;
    std::string token;
    std::vector<std::string> args;

    if (data.length() > 0) {
        if (data.find(" ") != std::string::npos) {
            for (size_t pos = 0; (pos = data.find(" ")) != std::string::npos; size++) {
                std::string token = data.substr(0, pos);
                if (size == 0)
                    id = handler_id_manager(token);
                else
                    args.push_back(token);
                data.erase(0, pos + 1);
            }
            if (data.length())
                args.push_back(data);
        } else
            id = handler_id_manager(data);
        if (id >= 0 && id <= 17)
            dispatchPacket(id, args, ent);
    }
}

int handler_id_manager(std::string data)
{
    int val = 0;

    if (data.length() == 0)
        return (-1);
    for (size_t i = 0; i < data.length(); i++)
        if (!(data[i] <= '9' && data[i] >= '0'))
            return (-1);

    return (atoi(data.c_str()));
}

