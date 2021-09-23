/*
** EPITECH PROJECT, 2019
** entity.cpp
** File description:
** entity
*/

#include <iostream>
#include <mutex>
#include <thread>
#include <bits/stdc++.h>

#include "entity.hpp"
#include "handler.hpp"
#include "server.hpp"

// # Builder / Destructor

entity::entity(void *_serv, boost::asio::ip::tcp::socket *_sock)
{
    serv = _serv;
    pseudo = std::string("undefined");
    address = _sock->remote_endpoint().address().to_string();
    port = -1;
    sock = _sock;
    std::vector<std::string> vec;
    sendToClient(0, vec); // Say Hello To Client
    asyncReceive();
}

entity::~entity()
{
    stop();
}

// # Methods

void entity::stop()
{
    sock->close();
}

void entity::procData(std::string data)
{
    const size_t length = data.size();
    for (size_t i = 0; i < length; ++i)
        printf("%3d (0x%02X)\n", data[i], data[i]);
    std::cout << "#Binary data : ";
    for (std::size_t i = 0; i < data.size(); ++i)
        std::cout << std::bitset<8>(data.c_str()[i]) << std::endl;
    std::cout << "#Clear data : " << data << std::endl;
}

void entity::asyncReceive()
{
    sock->async_receive(boost::asio::buffer(buffer, 512), [this](const boost::system::error_code &error, std::size_t bytesTransfered) {
        if (error != boost::system::errc::success) {
            std::cout << "Connection lost with user :" << pseudo << std::endl;
            server *s = (server*)serv;
            s->removeClient(pseudo);
            return;
        } else {
            std::string data;
            for (unsigned int i = 0; i < bytesTransfered && buffer[i]; i++)
                data += buffer[i];
            std::cout << "Received: ";
            procData(data);
            handleData(data);
        }
        asyncReceive();
    });
}

void entity::sendToClient(int id, std::vector<std::string> args)
{
    std::string val = std::to_string(id);
    for (unsigned int i = 0; i < args.size(); i++)
        val += " " + args[i];
    std::cout << "Sent: ";
    procData(val);
    sock->send(boost::asio::buffer(val, val.length()));
}

void entity::handleData(std::string data)
{
    handlePacket(data, this);
}

