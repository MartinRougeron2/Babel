/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** main
*/

#include "server.hpp"

server *servInst = new server(PORT);

void my_handler(int s)
{
    std::cout << "\b\bShuting down..." << std::endl;
    servInst->stop();

    exit(0);
}

int main(int ac, char **argv)
{
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
    servInst->acceptConnections();
    
    return (SUCCESS);
}

