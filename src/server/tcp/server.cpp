/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** server.cpp
*/

#include "../../../include/server/TCP.hpp"

TCP::TCP()
{
    this->port = TCP_PORT;
    TCP::build();
}

TCP::~TCP()
{
    
}

bool TCP::build_socket()
{
    this->address.sin_family = AF_INET;
    this->address.sin_addr.s_addr = htonl(INADDR_ANY);
    this->address.sin_port = htons(this->port);
    this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->server_socket >= 0)
        return (true);
    std::cerr << "Error establishing the server socket" << std::endl;
    return (false);
}

bool TCP::build_bind()
{
    this->server_bind = bind(this->server_socket, (struct sockaddr*) &this->address, sizeof(this->address));
    if (this->server_bind >= 0)
        return (true);
    std::cerr << "Error binding socket to local address" << std::endl;
    return (false);
}

bool TCP::build_listen()
{
    std::cout << "Waiting for a client to connect..." << std::endl;
    listen(this->server_socket, 10);
    this->server_udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (this->server_socket < 0) {
        std::cerr << "Error accepting request from client!" << std::endl;
        return (false);
    }
    std::cout << "Connected with client!" << std::endl;

    return (true);
}

bool TCP::build_accept()
{
    int ready = 0;

    FD_SET(this->server_socket, &this->rset);
    ready = select(1, &this->rset, NULL, NULL, NULL);
    if (FD_ISSET(this->server_socket, &this->rset)) {
        this->server_socket = accept(this->server_socket, (sockaddr *)&this->socket_address, &this->socket_size);
    }

    return (true);
}

bool TCP::run()
{
    this->running = true;

    for (; this->running == true; ) {
        TCP::build_accept();
        std::cout << "Awaiting client response..." << std::endl;
        memset(&msg, 0, sizeof(msg));
        recv(this->server_socket, (char*)&msg, sizeof(msg), 0);
        if(!strcmp(msg, "exit")) {
            std::cout << "Client has quit the session" << std::endl;
            this->running = false;
        }
        std::cout << "Client: " << msg << std::endl;
        std::cout << ":: ";
        std::string data;
        std::getline(std::cin, data);
        memset(&msg, 0, sizeof(msg));
        strcpy(msg, data.c_str());
        if (data == "exit") {
            send(this->server_socket, (char*)&msg, strlen(msg), 0);
            this->running = false;
        }
        send(this->server_socket, (char*)&msg, strlen(msg), 0);
    }
    std::cout << "Closing TCP server..." << std::endl;
    close(this->server_socket);
    close(this->server_socket);
    std::cout << "TCP server closed" << std::endl;

    return (true);
}

bool TCP::build_init()
{
    this->port = TCP_PORT;
    this->server_socket = 0;
    bzero((char*)&this->address, sizeof(this->address));
    this->socket_size = sizeof(this->socket_address);

    return (true);
}

bool TCP::build()
{
    TCP::build_init();
    TCP::build_socket();
    TCP::build_bind();
    TCP::build_listen();
    TCP::run();

    return (true);
}