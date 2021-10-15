/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** TCP
*/

#include "client/TCP.hpp"

using boost::asio::ip::tcp;

TCP::TCP()
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
}

TCP::~TCP()
{
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

std::string TCP::sendCommand(std::string command)
{
    boost::array<char, 128> buf;
    boost::system::error_code error;
    try {
        socket->send(boost::asio::buffer(command));
    } catch (std::exception &e) {
        this->_connected = false;
        socket->close();
        return "not connected";
    }
    size_t len = socket->read_some(boost::asio::buffer(buf), error);
    std::string data(reinterpret_cast<const char*>(buf.data()), len);
    return data;
}