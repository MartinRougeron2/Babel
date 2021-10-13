/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** TCP
*/

#include "client/TCP.hpp"

using boost::asio::ip::tcp;

TCP::TCP(boost::asio::io_context &io_context) : socket(io_context)
{
    try
    {
        tcp::resolver resolver(io_context);
        tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"), 2000);
        socket.connect(ep);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

TCP::~TCP()
{
}

std::string TCP::sendCommand(std::string command)
{
    boost::array<char, 128> buf;
    boost::system::error_code error;
    socket.send(boost::asio::buffer(command));
    size_t len = socket.read_some(boost::asio::buffer(buf), error);
    std::string data(reinterpret_cast<const char*>(buf.data()), len);
    std::cout << data << std::endl;
    return data;
}