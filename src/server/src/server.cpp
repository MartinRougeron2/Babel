/*
** EPITECH PROJECT, 2019
** server.cpp
** File description:
** server
*/

#include "server.hpp"
#include "network.hpp"
#include "handler.hpp"

// # Builder / Destructor

server::server(int port)
{
    net = new network(this, port);
}

server::~server()
{
    stop();
}

// # Methods

entry *server::getClientByAddress(std::string address)
{
    for (unsigned int i = 0; i < clients.size(); i++)
        if (clients[i]->address == address)
            return (clients[i]);
    return (NULL);
}

entry *server::getClientByPseudo(std::string pseudo)
{
    for (unsigned int i = 0; i < clients.size(); i++)
        if (clients[i]->pseudo.size() == pseudo.size() && clients[i]->pseudo == pseudo)
            return (clients[i]);
    return (NULL);
}

bool server::isPseudoAvailable(std::string pseudo)
{
    for (unsigned int i = 0; i < clients.size(); i++)
        if (clients[i]->pseudo.size() == pseudo.size() && clients[i]->pseudo == pseudo)
            return (false);
    return (true);
}

void server::removeClient(std::string pseudo)
{
    entry *ent = getClientByPseudo(pseudo);

    if (ent->pseudo.size())
        clients.erase(std::remove(clients.begin(), clients.end(), ent), clients.end());
}

void server::acceptConnections()
{
    running = true;
    net->start();
}

void server::handleClient()
{
    std::cout << "New client connected." << std::endl;
    clients.push_back(new entry(this, net->sockets.back()));
    net->sockets.pop_back();
}

void server::stop()
{
    net->stop();
    running = false;
    while (clients.size() != 0) {
        entry *entry = clients.back();
        entry->stop();
        clients.pop_back();
    }
}
