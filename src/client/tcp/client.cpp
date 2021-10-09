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

char *TCP::stca(const char *data)
{
    char *result = new char[strlen(data) + 1]; 
    result[strlen(data)] = '\0';

    for (int i = 0; i < strlen(data); i++) {
        result[i] = data[i];
    }

    return (result);
}

char *TCP::stca_(std::string data)
{
    char *result = new char[data.size() + 1]; 
    result[data.size()] = '\0';

    for (int i = 0; i < data.size(); i++) {
        result[i] = data[i];
    }

    return (result);
}

bool TCP::run()
{
    this->running = true;
    bool logged = false;
    std::string data;
    std::string logs;
    std::string full;

    for (; this->running == true; ) {
        if (logged == false) {
            std::cout << "login: username;pass" << std::endl;
            std::cout << "$> ";
            std::getline(std::cin, logs);
            logged = true;
            full = logs + ";/login";
        } else {
            std::cout << "$> ";
            std::getline(std::cin, data);
            memset(&msg, 0, strlen(msg));
            full = logs + ";" + data;
            std::cout << "command: " << full << std::endl;
        }
        strcpy(msg, full.c_str());
        if (data == "EXIT\n") {
            this->running = false;
        } else {
            send(this->client_socket, (char *)&msg, sizeof(msg), 0);
            std::cout << "Awaiting server response..." << std::endl;
            memset(&msg, 0, strlen(msg));
            recv(this->client_socket, (char *)&msg, sizeof(msg), 0);
            std::cout << "Received: " << msg << std::endl;
        }
    }
    close(this->client_socket);

    return (true);
}