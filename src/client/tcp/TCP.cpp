/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** TCP
*/

#include "client/TCP.hpp"
#include "../GUI/App.h"
#include "../GUI/UserMenu.h"

using boost::asio::ip::tcp;

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <thread>

TCP::TCP(App *appCopy) : strand(io_context)
{
    try
    {
        io_context.run();
        tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 2000);
        socket = new tcp::socket(io_context);
        socket->connect(ep);
        std::thread reader(&TCP::async_read, this);
        reader.detach();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        socket->close();
        this->_connected = false;
        return;
    }
    this->_connected = true;
    this->copy = appCopy;
}

TCP::~TCP()
{
    this->socket->close();
}

void TCP::doConnect()
{
    try
    {
        tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 2000);
        socket = new tcp::socket(io_context);
        socket->connect(ep);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        this->_connected = false;
        socket->close();
        return;
    }
    this->_connected = true;
}

void TCP::read(const boost::system::error_code &error, size_t bytes_recvd)
{
    std::cout << "read start" << std::endl;
    if (error) {
        std::cout << error.message() << std::endl;
        return;
    }
    auto raw = security::decoder(buf);
    std::cout << "read" << raw << std::endl;
    if (raw.substr(0, raw.find('?')) == "accept") {
        this->copy->setGroupId(std::atoi(raw.substr(raw.find('?')).c_str()));
        UserMenu *menu = this->copy->getUsermenu();
        menu->getCallW()->setScene(Call::RECEIVECALL, "On vous appelle");
        buf.assign(0);
    }
    async_read();
}

void TCP::async_read()
{
    this->socket->receive(
        boost::asio::buffer(buf)
    );
    auto raw = security::decoder(buf);
    if (raw.substr(0, raw.find('?')) == "accept") {
        std::cout << "find ?" << std::endl;
        this->copy->setGroupId(std::atoi(raw.substr(raw.find('?')).c_str()));
        UserMenu *menu = this->copy->getUsermenu();
        menu->getCallW()->setScene(Call::RECEIVECALL, "On vous appelle");
        buf.assign(0);
    }
    async_read();
}

std::string TCP::sendCommand(std::string command)
{
    boost::array<std::bitset<16>, max_length> encoded = security::encoder(command);
    boost::system::error_code error;
    std::string raw;

    try {
        socket->send(
            boost::asio::buffer(
                encoded,
                max_length
            )
        );
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
        this->_connected = false;
        return "not connected";
    }
    usleep(10000);
    raw = security::decoder(buf);
    buf.assign(0);
    encoded.assign(0);
    return raw;
}