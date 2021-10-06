/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** server.cpp
*/

#include "client/TCP.hpp"

TCP::TCP()
{
    this->server_ip = TCP_IP;
    this->server_port = TCP_PORT;

    TCP::build();
}

TCP::~TCP()
{  
}

bool TCP::build_init()
{
    bzero((char*)&this->address, sizeof(this->address));
    this->host = gethostbyname(this->server_ip);
    this->address.sin_family = AF_INET; 
    this->address.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    this->address.sin_port = htons(this->server_port);
    this->client_socket = socket(AF_INET, SOCK_STREAM, 0);
    this->client_status = connect(this->client_socket, (sockaddr*) &this->address, sizeof(this->address));

    return (true);
}

bool TCP::build_connect()
{
    if (this->client_status < 0) {
        std::cout << "Error connecting to socket !" << std::endl;
        return (false);
    }
    std::cout << "Connected to:" << std::endl;
    std::cout << "Host: " << this->server_ip << std::endl;
    std::cout << "Port: " << this->server_port << std::endl;

    return (true);
}

bool TCP::build()
{
    TCP::build_init();
    TCP::build_connect();
    TCP::run();

    return (true);
}

bool TCP::run()
{
    this->running = true;
    // command
    Commands command;
    User user;
    Protocol data;

    // TO REMOVE FORCE LOGIN
    user.username = "admin";
    user.password = "admin";
    user.address = "127.0.0.1";

    for (; this->running == true; ) {
        std::cout << "$> ";
        std::cin >> command.command >> command.arguments;
        if (data.command.command == "EXIT") {
            this->running = false;
        }
        send(this->client_socket, &data, sizeof(data), 0);
    }
    close(this->client_socket);

    return (true);
}