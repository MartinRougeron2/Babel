/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** test
*/

#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>




int udp__()
{
   std::uint16_t port = 15001;

    boost::asio::io_context io_context;
    boost::asio::ip::udp::endpoint receiver(boost::asio::ip::udp::v4(), port);
    boost::asio::ip::udp::socket socket(io_context, receiver);

    for(;;)
    {
        char buffer[65536];
        boost::asio::ip::udp::endpoint sender;
        std::size_t bytes_transferred = socket.receive_from(boost::asio::buffer(buffer), sender);
        socket.send_to(boost::asio::buffer(buffer, bytes_transferred), sender);
    }
    return 0;
}