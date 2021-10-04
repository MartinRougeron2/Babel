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
    int bytesRead = 0;
    int bytesWritten = 0;
    this->running = true;

    for (; this->running == true; ) {
        std::cout << ":: ";
        std::string data;
        std::getline(std::cin, data);
        memset(&msg, 0, sizeof(msg));
        strcpy(msg, data.c_str());

        if (data == "exit") {
            send(this->client_socket, (char*)&msg, strlen(msg), 0);
            this->running = false;
        }
        bytesWritten += send(this->client_socket, (char*)&msg, strlen(msg), 0);
        std::cout << "Awaiting server response..." << std::endl;
        memset(&msg, 0, sizeof(msg));
        bytesRead += recv(this->client_socket, (char*)&msg, sizeof(msg), 0);
        if (!strcmp(msg, "exit")) {
            std::cout << "Server has quit the session" << std::endl;
            this->running = false;
        }
        std::cout << "Received: " << msg;
    }
    close(this->client_socket);

    return (true);
}