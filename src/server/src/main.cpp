/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** main
*/

// # Lib Imports

// # Local Imports

#include "server.hpp"

// # Values

static const int success = 0;
static const int fail = 84;
static const int port = 2000;
server *servInst = new server(port);

// # Methods

void my_handler(int s) {
    (void)s;
    std::cout << "Shuting down..." << std::endl;
    servInst->stop();
    exit(0);
}

int main(int ac, char **as)
{
    struct sigaction sigIntHandler;

    (void)ac;
    (void)as;
    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
    servInst->acceptConnections();
    return (success);
}

