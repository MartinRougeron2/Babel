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
    #include <QWidget>

    #include "security.hpp"

    #define TCP_IP "127.0.0.1"
    #define TCP_PORT 2000

    class TCP
    {
        public:
            TCP();
            ~TCP();

            std::string sendCommand(std::string command);
            bool isConnected() { sendCommand("/ping"); return this->_connected;};
            void doConnect();
        private:
            boost::asio::io_context io_context;
            boost::asio::ip::tcp::socket *socket;
            bool _connected = true;
    };

#endif /* TCP_HPP */