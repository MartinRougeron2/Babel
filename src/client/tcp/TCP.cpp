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

TCP::TCP(App *appCopy) : strand(io_context)
{
    try
    {
        io_context.run();
        tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 2000);
        socket = new tcp::socket(io_context);

        socket->connect(ep);
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
    this->async_read();
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
    std::cout << "yes" << std::endl;
}

void TCP::read(const boost::system::error_code &error, size_t bytes_recvd)
{
    if (error) {
        std::cout << error.message();
        return;
    }
    auto raw = security::decoder(buf);
    buf.assign(0);
    if (raw.substr(0, raw.find('?')) == "accept") {
        this->copy->setGroupId(std::atoi(raw.substr(raw.find('?')).c_str()));
        UserMenu *menu = this->copy->getUsermenu();
        menu->getCallW()->setScene(Call::RECEIVECALL, "On vous appelle");
    }
    async_read();
}

void TCP::async_read()
{
    this->socket->async_receive(
        boost::asio::buffer(buf),
        strand.wrap(
            boost::bind(
                &TCP::read,
                this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred
            )
        )
    );
}

std::string TCP::sendCommand(std::string command)
{
    boost::array<std::bitset<16>, max_length> buffer = {0};
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
    socket->read_some(
        boost::asio::buffer(
            buffer,
            max_length
        ),
        error
    );
    raw = security::decoder(buffer);
    buf.assign(0);
    encoded.assign(0);

    return raw;
}