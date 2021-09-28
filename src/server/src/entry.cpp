/*
** EPITECH PROJECT, 2019
** entry.cpp
** File description:
** entry
*/

#include <iostream>
#include <mutex>
#include <thread>
#include <bits/stdc++.h>

#include "entry.hpp"
#include "handler.hpp"
#include "server.hpp"
#include "logs.hpp"

entry::entry(void *_serv, boost::asio::ip::tcp::socket *_sock)
{
    serv = _serv;
    pseudo = std::string("undefined");
    address = _sock->remote_endpoint().address().to_string();
    port = -1;
    socket_id = _sock;
    std::vector<std::string> vec;

    sendToClient(0, vec);
    asyncReceive();
}

entry::~entry()
{
    stop();
}

void entry::stop()
{
    socket_id->close();
}


void entry::resume(std::string data)
{
    const size_t length = data.size();

    std::cout << " dec | hexa | oct |  binary  " << std::endl;
    std::cout << "-----|------|-----|----------" << std::endl;

    for (size_t i = 0; i < length; ++i) {
        std::cout << " " << std::left << std::setw(4) << std::dec << (int)data[i];
        std::cout << "| 0x" << std::left << std::setw(3) << std::hex << (int)data[i];
        std::cout << "| " << std::left << std::setw(4) << std::oct << (int)data[i];
        std::cout << "| " << std::left << std::setw(8) << std::bitset<8>(data.c_str()[i]) << std::endl;
    }
    std::cout << std::endl;
    std::cout << COLOR_GREEN << "Clear data\n-----------------------------\n" << COLOR_RESET << std::endl << data << std::endl;
}

void entry::asyncReceive()
{
    socket_id->async_receive(boost::asio::buffer(buffer, 512), [this](const boost::system::error_code &error, std::size_t bytesTransfered) {
        if (error != boost::system::errc::success) {
            std::cout << pseudo << death.at(rand() % 32) << std::endl;
            server *s = (server*)serv;
            s->remove_username(pseudo);
        } else {
            std::string data;
            for (size_t i = 0; i < bytesTransfered && buffer[i]; i++)
                data += buffer[i];
            std::cout << COLOR_CYAN << "\nReceived\n-----------------------------\n" << COLOR_RESET << std::endl;
            resume(data);
            handleData(data);
        }
        asyncReceive();
    });
}

void entry::sendToClient(int id, std::vector<std::string> args)
{
    std::string val = std::to_string(id);

    for (size_t i = 0; i < args.size(); i++)
        val += " " + args[i];
    std::cout << COLOR_RED << "Sent\n-----------------------------\n" << COLOR_RESET << std::endl;
    resume(val);
    socket_id->send(boost::asio::buffer(val, val.length()));
}

void entry::handleData(std::string data)
{
    packet_handler(data, this);
}
