/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** TCP.hpp
*/

#ifndef TCP_HPP
    #define TCP_HPP

    #include <iostream>
    #include <string>
    #include <boost/array.hpp>
    #include <boost/asio.hpp>

    #include "Protocol.hpp"

    #define TCP_IP "127.0.0.1"
    #define TCP_PORT 2000

    class TCP
    {
        public:
            TCP(boost::asio::io_context &io_context);
            ~TCP();

            std::string sendCommand(std::string command);
        private:
            boost::asio::ip::tcp::socket socket;
    };

#endif /* TCP_HPP */