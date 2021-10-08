/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Group.cpp
*/

#include "server/UdpServer.hpp"
#include "../../../include/server/UdpServer.hpp"


Group::Group()
{
}

Group::Group(shared_session session)
{
    this->sessions.push_back(session);
}

Group::Group(std::vector<shared_session> sessions)
{
    for (auto &session : sessions)
        this->sessions.push_back(session);
}

Group::~Group()
{
}

void Group::addSession(shared_session session)
{
    this->sessions.push_back(session);
}

void Group::addSession(std::vector<shared_session> sessions)
{
    for (auto &session: sessions)
        this->sessions.push_back(session);
}